/*
 * GameManager.cpp
 *
 *  Created on: Oct. 10, 2018
 *      Author: ericz
 */

#include "GameManager.h"
#include "../obj/ExplosionParticle.h"
#include "../obj/GameObject.h"
#include "../obj/HomingEnemy.h"
#include "../obj/MoveEnemy.h"
#include "../obj/MoveParticle.h"
#include "../obj/PlayerObject.h"
#include "EnemyManager.h"
#include "GameInput.h"
#include "GameRenderer.h"
#include <cmath>
#include "../obj/CheckpointParticle.h"

#ifdef _WIN32
#include "SDL_image.h"
#include "SDL_mixer.h"
#else
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#endif

//The music that will be played
Mix_Music *music = NULL;

//The sound effects that will be used
Mix_Chunk *hurt = NULL;
Mix_Chunk *collect = NULL;
using namespace std;

//declare pointers to game objects
vector<shared_ptr<GameObject>> GameManager::activeObjects{};
std::shared_ptr<PlayerObject> GameManager::activePlayer = nullptr;
std::shared_ptr<GameObject> GameManager::bg1 = nullptr;
std::shared_ptr<GameObject> GameManager::bg2 = nullptr;
std::shared_ptr<GameObject> GameManager::bg3 = nullptr;
std::shared_ptr<GameObject> GameManager::bg4 = nullptr;
std::vector<std::shared_ptr<Enemy>> GameManager::activeEnemies{};
std::vector<std::shared_ptr<Checkpoint>> GameManager::activeCheckpoints{};
std::vector<std::shared_ptr<UIElement>> GameManager::activeElements{};
float GameManager::parallaxPosition1 = SCREEN_HEIGHT;
float GameManager::parallaxPosition2 = 0;
float GameManager::backgroundPosition1 = SCREEN_HEIGHT;
float GameManager::backgroundPosition2 = 0;
int GameManager::idGenerator = 0;
const float SCREEN_CENTER = SCREEN_WIDTH / 2;
bool GameManager::playerMade = false;

//declare time clock for game
extern std::chrono::high_resolution_clock::time_point CURRENT_TIME = chrono::high_resolution_clock::now();
extern int FRAME_TIME = 0;

double GameManager::playerScore = 0;
double GameManager::scoreMultiplier = 1.0;

//method to add objects to the game (used for all game objects including player and enemy)
void GameManager::AddObject(shared_ptr<GameObject> newObj) {
    //add object to active object vector
    activeObjects.push_back(newObj);
    newObj->SetID(idGenerator);
    idGenerator++;

    string tag = newObj->GetTag();
    if (tag == "Player")
        //create player object
        activePlayer = dynamic_pointer_cast<PlayerObject>(newObj);
    else if (tag == "MoveEnemy" || tag == "WallEnemy" || tag == "HomingEnemy")
        //create enemy object
        activeEnemies.push_back(dynamic_pointer_cast<Enemy>(newObj));
    else if (tag == "Checkpoint")
        //create checkpoint object
        activeCheckpoints.push_back(dynamic_pointer_cast<Checkpoint>(newObj));
}

//remove object from object vector
void GameManager::RemoveObjectFromList(int id) {
    //traverse through vector until id equals vector index
    for (int i = 0; i < activeObjects.size(); i++) {
        if (activeObjects[i]->GetID() == id) {
            activeObjects.erase(activeObjects.begin() + i);
        }
    }
}

void GameManager::LogicStep() {
    //Cannot use C++11 iterators, as the vector size may change during the Logic()
    //step. Must check if the size has changed using old-fashioned for loops.
    /*
	for (auto& object : activeObjects) {
		object->Logic();
	}
	*/
    //test for deletion first
    for (int i = 0; i < activeObjects.size(); i++) {
        activeObjects[i]->Logic();
        //test if the object was marked to be deleted
        if (activeObjects[i]->WillBeDeleted) {
            //delete object from vector
            activeObjects.erase(activeObjects.begin() + i);
            i--;
        }
    }
    //look at enemy objects and add force if it is a moving enemy
    for (int i = 0; i < activeEnemies.size(); i++) {
        /*if (activeEnemies[i]->GetTag() == "MoveEnemy") {
            activeEnemies[i]->AddForce(0, 0.1);
        }*/

        if (activeEnemies[i]->WillBeDeleted) {
            activeEnemies.erase(activeEnemies.begin() + i);
            i--;
        }
    }

    for (int i = 0; i < activeCheckpoints.size(); i++) {
        /*if (activeEnemies[i]->GetTag() == "MoveEnemy") {
            activeEnemies[i]->AddForce(0, 0.1);
        }*/

        if (activeCheckpoints[i]->WillBeDeleted) {
            activeCheckpoints.erase(activeCheckpoints.begin() + i);
            i--;
        }
    }

    //check if active player should be deleted (ran out of lives)
    if (activePlayer != nullptr && activePlayer->WillBeDeleted) {
        activePlayer = nullptr;
    }
}

SDL_Surface* background_surface = NULL;
SDL_Texture* background_texture = NULL;
SDL_Renderer* renderer = NULL;


void GameManager::RenderStep() {
    renderer = GameRenderer::GetRenderer().get();
    SDL_RenderClear(renderer);

    for (auto& object : activeObjects) {
        SDL_RenderCopyEx(renderer, object->GetTexture().get(), NULL, object->GetRect(), object->GetAngle(), NULL, SDL_FLIP_NONE);
    }
}

//call for ui menus
void GameManager::UIStep(UIManager& ui) {
    ui.Logic();
    for (auto& element : ui.CurrentMenu().elementList) {
        SDL_RenderCopy(GameRenderer::GetRenderer().get(), element->GetTexture().get(), NULL, element->GetRect());
    }
}

//check for collisions
void GameManager::HandleCollisions() {
    //set initial bool to false and test to see if collision and mark as true
    bool hasCollided = false;
    //check enemy collisions first (all types of enemy)
    for (auto& enemy : activeEnemies) {
        if (enemy->CircleInBounds(activePlayer->position[0], activePlayer->position[1], activePlayer->GetHitCircleSize()) && !activePlayer->IsInvincible() && !hasCollided) {
            //enemy->DamagePlayer(*activePlayer);
            double centerX = enemy->GetRect()->x + (enemy->GetRect()->w / 2);
            double centerY = enemy->GetRect()->y + (enemy->GetRect()->h / 2);
            double ratio = (double)(enemy->GetRect()->w) / (double)(enemy->GetRect()->h);
            double differenceX = (activePlayer->position[0] - centerX) * ratio;
            double differenceY = activePlayer->position[1] - centerY;
            cout << "centerX " << centerX << " centerY " << centerY << " dX " << differenceX << " dY " << differenceY << " ratio " << ratio << endl;
            //if a collition create a bounce back
            if ((std::abs((long)(differenceX)) > std::abs((long)differenceY))) {
                if (differenceX <= 0)
                    activePlayer->AddForce(-20, 0);
                else if (differenceX > 0)
                    activePlayer->AddForce(20, 0);
            } else {
                if (differenceY <= 0)
                    activePlayer->AddForce(0, -20);
                else if (differenceY > 0)
                    activePlayer->AddForce(0, 20);
            }
            //create an explosion to indicate a collision
            AddObject(make_shared<ExplosionParticle>(enemy->position[0], enemy->position[1]));
            hasCollided = true;
            //mark for enemy to be deleted
            enemy->MarkForDeletion();
            //reduce life from player
            activePlayer->TakeLife();

            Mix_PlayChannel( -1, hurt, 0);

        }
    }
    //next check if the player has collided with a checkpoint
    for (auto& check : activeCheckpoints) {
            check->position[1] += 2;
        if (check->position[1] > GameRenderer::getScreenHeight()+10)
            check->MarkForDeletion();

        if (check->CircleInBounds(activePlayer->position[0], activePlayer->position[1], activePlayer->GetHitCircleSize()) && !activePlayer->IsInvincible() && !hasCollided) {
            UIManager::getPointsText->positionx = check->position[0];
            UIManager::getPointsText->positiony = check->position[1];
            UIManager::getPointsVelocity = -5;

            Mix_PlayChannel( -1, collect, 0);
            int x = rand() % GameRenderer::getScreenWidth();
            int y = rand() % (GameRenderer::getScreenHeight() - 600);
            AddObject(make_shared<CheckpointParticle>(check->position[0], check->position[1]));
            double addScore = 10 * EnemyManager::GetDifficulty() * scoreMultiplier;
            
            UIManager::getPointsText->ChangeText("+" + to_string((int)addScore));
            cout << "text position is now: " << UIManager::getPointsText->positionx << " " << UIManager::getPointsText->positiony << endl;

            playerScore += addScore;
            GameManager::scoreMultiplier *= 1.025;
            cout << "scoreMultiplier: " << scoreMultiplier << endl;
            check->CollidePlayer(*activePlayer, -100, -100);
            check->MarkForDeletion();
            /*EnemyManager::ClearStaticEnemies();
            EnemyManager::GenerateStaticEnemies();*/
        }
    }
}

void GameManager::StartGame() {
    int max_height = GameRenderer::getScreenHeight();
    int max_width = GameRenderer::getScreenWidth();
    int seed = static_cast<int>(time(0));
    srand(seed);

    //set initial score as well as text placement
    playerScore = 0;
    scoreMultiplier = 1.0;
    UIManager::getPointsText->positionx = -100;
    UIManager::getPointsText->positiony = -100;

    //load background pictures
    shared_ptr<GameObject> backgroundObj = make_shared<GameObject>("Background.png", (max_width / 2), 0 + max_height/2, max_width, max_height);
    shared_ptr<GameObject> backgroundObj2 = make_shared<GameObject>("Background.png", (max_width / 2), -max_height + max_height/2, max_width, max_height);
    shared_ptr<GameObject> backgroundObj3 = make_shared<GameObject>("Background2.png", (max_width / 2), 0 + max_height/2, max_width, max_height);
    shared_ptr<GameObject> backgroundObj4 = make_shared<GameObject>("Background2.png", (max_width / 2), -max_height + max_height/2, max_width, max_height);
    bg1 = dynamic_pointer_cast<GameObject>(backgroundObj);
    bg2 = dynamic_pointer_cast<GameObject>(backgroundObj2);
    bg3 = dynamic_pointer_cast<GameObject>(backgroundObj3);
    bg4 = dynamic_pointer_cast<GameObject>(backgroundObj4);
    AddObject(backgroundObj);
    AddObject(backgroundObj2);
    AddObject(backgroundObj3);
    AddObject(backgroundObj4);

    //make checkpoint
    /*
    int x = rand() % max_width;
    int y = rand() % (max_height - 600);  // prevent spawning on top 300 pixels of screen
    shared_ptr<Checkpoint> checkpointObj = make_shared<Checkpoint>(x, y, 32, 32);
    AddObject(checkpointObj);
    */

    //make enemies
    //EnemyManager::GenerateStaticEnemies();
}

void GameManager::RestartGame(){
    EnemyManager::ResetManager();
    GameManager::ClearScreen();
    GameManager::StartGame();
}

void GameManager::ClearScreen() {
    //erase all object (point to null ptr)
    for (int i = 0; i < activeObjects.size(); i++) {
        activeObjects.erase(activeObjects.begin() + i);
        i--;
    }
}

void GameManager::ClearEnemies() {
    //note: requires a cycle through the game loop to work
    for (auto& enemy : activeEnemies) {
        AddObject(make_shared<ExplosionParticle>(enemy->position[0], enemy->position[1]));
        //mark for enemy to be deleted
        enemy->MarkForDeletion();
    }
}

void GameManager::ClearCheckpoints() {
    //note: requires a cycle through the game loop to work
    for (auto& checkpoint : activeCheckpoints) {
        //mark for checkpoint to be deleted
        checkpoint->MarkForDeletion();
    }
}

void GameManager::updateScore() {
    //make scoring system such that difficulty and frametime will build the total score
    playerScore += EnemyManager::GetDifficulty() * FRAME_TIME * 0.005;
    //set text to show score
    string newScore = "Score: " + to_string(int(playerScore));
    UIManager::scoreText->ChangeText(newScore);
    UIManager::finalScoreText->ChangeText(newScore);

    //update lives of the active player
    if (activePlayer != nullptr) {
        string newLives = "Lives: " + to_string(activePlayer->GetLives());
        UIManager::livesText->ChangeText(newLives);
    }
    else
        UIManager::livesText->ChangeText("Lives: 0");
}


int main(int argc, char* args[]) {
    GameRenderer::Initialize();
    UIManager ui;
    GameInput in;
    GameManager::StartGame();
    int max_height = GameRenderer::getScreenHeight();
    int max_width = GameRenderer::getScreenWidth();
    //Initialize SDL_mixer
    Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );
    music = Mix_LoadMUS( "Asriel Dreemur.mp3" );
    hurt = Mix_LoadWAV( "hurt.wav" );
    collect = Mix_LoadWAV( "collect.wav" );
    //AddObject(backgroundObj);
    Mix_PlayMusic( music, -1 );
    int endGameCounter = 0; // keeps the game alive for x frames after the player dies
    
    UIManager::getPointsText->positionx = -100;
    UIManager::getPointsText->positiony = -100;

    while (!GameInput::IsQuitting()) {
        //Get the time elapsed since the last loop execution.
        auto newCurrentTime = chrono::high_resolution_clock::now();
        FRAME_TIME = std::chrono::duration_cast<std::chrono::milliseconds>(newCurrentTime - CURRENT_TIME).count();
        CURRENT_TIME = newCurrentTime;

        //check for user inputs
        in.HandleEvent();
        vector<int> direction = in.GetDirectionInput();

        //get background position with level of difficulty and frame time
        GameManager::backgroundPosition1 += FRAME_TIME * 0.08 * EnemyManager::GetDifficulty();
        GameManager::backgroundPosition2 += FRAME_TIME * 0.08 * EnemyManager::GetDifficulty();
        GameManager::parallaxPosition1 += FRAME_TIME * 0.02 * EnemyManager::GetDifficulty();
        GameManager::parallaxPosition2 += FRAME_TIME * 0.02 * EnemyManager::GetDifficulty();

        //set background position
        GameManager::bg1->position[1] = GameManager::backgroundPosition1;
        GameManager::bg2->position[1] = GameManager::backgroundPosition2;
        GameManager::bg3->position[1] = GameManager::parallaxPosition1;
        GameManager::bg4->position[1] = GameManager::parallaxPosition2;

        if (GameManager::backgroundPosition1 > SCREEN_HEIGHT * 1.5) GameManager::backgroundPosition1 -= SCREEN_HEIGHT * 2;
        if (GameManager::backgroundPosition2 > SCREEN_HEIGHT * 1.5) GameManager::backgroundPosition2 -= SCREEN_HEIGHT * 2;
        if (GameManager::parallaxPosition1 > SCREEN_HEIGHT * 1.5) GameManager::parallaxPosition1 -= SCREEN_HEIGHT * 2;
        if (GameManager::parallaxPosition2 > SCREEN_HEIGHT * 1.5) GameManager::parallaxPosition2 -= SCREEN_HEIGHT * 2;

        //check to see if the game is running
        if (ui.getMenuState() == INGAME) {
            //make player
            if (!GameManager::playerMade) {
                shared_ptr<PlayerObject> playerObj = make_shared<PlayerObject>(max_width/2, max_height/2);
                GameManager::AddObject(playerObj);
                GameManager::playerMade = true;
            }

            EnemyManager::Update();
            
            //Only look at keyboard inputs when the game has been started (from either menu)
            if (GameManager::activePlayer != nullptr) {
                if (direction[HORIZONTAL] == LEFT)
                    GameManager::activePlayer->AddForce(-1, 0);
                if (direction[HORIZONTAL] == RIGHT)
                    GameManager::activePlayer->AddForce(1, 0);
                if (direction[VERTICAL] == UP)
                    GameManager::activePlayer->AddForce(0, -1);
                if (direction[VERTICAL] == DOWN)
                    GameManager::activePlayer->AddForce(0, 1);
            }
            //if player is alive, check for collisions and update accordingly
            if (GameManager::activePlayer != nullptr) {
                GameManager::HandleCollisions();
                GameManager::updateScore();
            }

            //if the player is out of lives and deleted end game
            if (GameManager::activePlayer == nullptr) {
                endGameCounter += FRAME_TIME;
                if(endGameCounter >= 2000){
                    GameManager::ClearEnemies();
                    GameManager::ClearCheckpoints();
                    GameManager::ClearScreen();
                    endGameCounter = 0;
                    ui.ChangeState(MenuState::QUITGAME);
                }
            }

            UIManager::getPointsText->positiony += UIManager::getPointsVelocity;
            UIManager::getPointsVelocity += FRAME_TIME * 0.025;

            UIManager::getPointsText->UpdatePosition(UIManager::getPointsText->positionx, UIManager::getPointsText->positiony);
            //cout << UIManager::getPointsText->positiony << " " << UIManager::getPointsVelocity << endl;
        }
        else {
            if (GameManager::playerMade) GameManager::playerMade = false;
        }

        //continue through steps with screen rendering and check menu rendering
        //DO NOT MOVE THIS. If you need to hide an object, remove it from the active list.
        GameManager::LogicStep();
        GameManager::RenderStep();
        GameManager::UIStep(ui);
        SDL_RenderPresent(GameRenderer::GetRenderer().get());
    }

    //set music
    Mix_FreeMusic( music );
    return 0;
}

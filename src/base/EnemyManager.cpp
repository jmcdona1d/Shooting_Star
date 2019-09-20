/*
 * EnemyManager.cpp
 *
 *  Created on: Nov. 15, 2018
 *      Author: James Ford
 */

#include "EnemyManager.h"
#include "../obj/MoveEnemy.h"
#include "../obj/WallEnemy.h"
#include "../obj/HomingEnemy.h"
#include "GameManager.h"

using namespace std;

extern int FRAME_TIME;
float EnemyManager::difficulty = INITIAL_DIFFICULTY;
float EnemyManager::moveTimer = 0;
float EnemyManager::wallTimer = 0;
float EnemyManager::homingTimer = 0;
float EnemyManager::checkTimer = 0;

void EnemyManager::GenerateMovingEnemy() {
    int x = rand() % GameRenderer::getScreenWidth();
    //generate from top of screen
    int y = -100; 

    shared_ptr<MoveEnemy> newEnemy = make_shared<MoveEnemy>(x, y, MOVING_ENEMY_SIZE, MOVING_ENEMY_SIZE);
    //generate new moving enemy
    GameManager::AddObject(newEnemy); 
}

void EnemyManager::GenerateHomingEnemy() {
    //create random placement in x
	int x = rand() %  GameRenderer::getScreenWidth();
    //int y = -100;
	//create random placement in y
    int y = rand() %  GameRenderer::getScreenHeight(); 
    int w = 32;
    int h = 32;
	double l = 4000;

    shared_ptr<HomingEnemy> newEnemy;
    int direction = rand() % 4;

    switch (direction) {
    case 0:
        newEnemy = make_shared<HomingEnemy>(-100, y,  MOVING_ENEMY_SIZE, MOVING_ENEMY_SIZE, l);
        break;
    case 1:
        newEnemy = make_shared<HomingEnemy>(SCREEN_WIDTH + 100, y,  MOVING_ENEMY_SIZE, MOVING_ENEMY_SIZE, l);
        break;
    case 2:
        newEnemy = make_shared<HomingEnemy>(x, -100,  MOVING_ENEMY_SIZE, MOVING_ENEMY_SIZE, l);
        break;
    case 3:
        newEnemy = make_shared<HomingEnemy>(x, SCREEN_HEIGHT + 100,  MOVING_ENEMY_SIZE, MOVING_ENEMY_SIZE, l);
        break;
    }
    GameManager::AddObject(newEnemy);
}

void EnemyManager::GenerateStaticEnemy()
{
    int x;
    int y;
    //generate random x position
    x = rand() % GameRenderer::getScreenWidth();
    y =  -200;

    shared_ptr<WallEnemy> newEnemy = make_shared<WallEnemy>(x, y, WALL_SIZE, WALL_SIZE);
    GameManager::AddObject(newEnemy);
}

void EnemyManager::GenerateCheckpoint()
{
    int x;
    int y;
    //generate random x position
    x = rand() % GameRenderer::getScreenWidth();
    y =  -30;

    shared_ptr<Checkpoint> newEnemy = make_shared<Checkpoint>(x, y, 32, 32);
    GameManager::AddObject(newEnemy);
}

//add walls to game
void EnemyManager::GenerateStaticEnemies() {
    int x;
    int y;
    int wallsAdded = 0;
    for (int i = 0; i < 100; i++) {
        //test to see if there are the maximum number of walls
        if (wallsAdded == NUM_WALLS) break;

        x = rand() % GameRenderer::getScreenWidth();
        y = rand() % GameRenderer::getScreenHeight();

        //make placement of walls true until checked
        bool validPlacement = true;
        for (auto &currentEnemy : GameManager::activeEnemies) {
            //check to see if there is collision with other enemy
            if ((currentEnemy->GetTag() == "WallEnemy") && (currentEnemy->CircleInBounds(x, y, WALL_SIZE / 2 + MIN_SPACE_BETWEEN_WALLS))) {
                validPlacement = false;
                break;
            }
        }
        
        //check if the wall conflicts with the active player
        if ((GameManager::activePlayer != nullptr) && (GameManager::activePlayer->CircleInBounds(x, y, (WALL_SIZE / 2) + MIN_SPACE_BETWEEN_WALLS))) {
            validPlacement = false;
        }

        //check if conflicting with the checkpoint
        for (auto &check : GameManager::activeCheckpoints) {
            if (check->CircleInBounds(x, y, (WALL_SIZE / 2) + MIN_SPACE_BETWEEN_WALLS)) {
                validPlacement = false;
            }
        }

        //add new wall after all tests
        if (validPlacement) {
            shared_ptr<WallEnemy> newEnemy = make_shared<WallEnemy>(x, y, WALL_SIZE, WALL_SIZE);
            GameManager::AddObject(newEnemy);
            wallsAdded++;
        }
    }
}

//delete function for wall
void EnemyManager::ClearStaticEnemies() {
    for (int i = 0; i < GameManager::activeEnemies.size(); i++) {
        if (GameManager::activeEnemies[i]->GetTag() == "WallEnemy") {
            //delete walls
            GameManager::activeEnemies[i]->MarkForDeletion();
        }
    }
}

void EnemyManager::Update() {
    //increase moveTimer (speed) by difficulty scale in each update
    moveTimer += difficulty;
    if (moveTimer > INTERVAL_MOVE) {
        moveTimer = 0 + (moveTimer - INTERVAL_MOVE);
        //generate new moving enemy with updated timer
        EnemyManager::GenerateMovingEnemy();
    }
    
    //increase wallTimer by difficulty scale in each update
    wallTimer += difficulty;
    if (wallTimer > INTERVAL_WALL) {
        wallTimer = 0 + (wallTimer - INTERVAL_WALL);
        //generate new static enemy with updated timer
        EnemyManager::GenerateStaticEnemy();
    }

    //checkTimer is not difficulty dependent
    checkTimer += FRAME_TIME;
    if (checkTimer > INTERVAL_CHECKPOINT) {
        checkTimer = 0 + (checkTimer - INTERVAL_CHECKPOINT);
        EnemyManager::GenerateCheckpoint();
		
    }

    //increase homingTimer by difficulty scale in each update
    homingTimer += difficulty;
    if ((homingTimer > INTERVAL_HOMING) && difficulty >= HOMING_MIN_DIFFICULTY) {
        homingTimer = 0 + (homingTimer - INTERVAL_HOMING);
        EnemyManager::GenerateHomingEnemy();
    }

    difficulty += (float)FRAME_TIME * DIFFICULTY_RATE;
    //cout << "difficulty: " << difficulty << " moveTimer: " << moveTimer << endl;
}

//set timers and difficulty to initial and 0
void EnemyManager::ResetManager() {
    difficulty = INITIAL_DIFFICULTY;
    moveTimer = 0;
    wallTimer = 0;
    checkTimer = 0;
    homingTimer = 0;
}

//difficulty accessor
float EnemyManager::GetDifficulty() {
    return difficulty;
}
/*
 * GameManager.h
 *
 *  Created on: Oct. 10, 2018
 *      Author: ericz
 */

#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_

#include <chrono>
#include "../obj/Checkpoint.h"
#include "../obj/Enemy.h"
#include "../obj/GameObject.h"
#include "../obj/PlayerObject.h"
#include "../ui/UIElement.h"
#include "../ui/UIManager.h"
#include "GameRenderer.h"

//const int MIN_SPACE_BETWEEN_OBJECTS = 100;

class GameManager {
   public:
    /*
	 * GameManager::LogicStep()
	 * Runs the Logic() function within each GameObject in activeObjects;
	 * the LogicStep is executed every frame before rendering.
	 */
    static void LogicStep();

    /*
	 * GameManager::RenderStep()
	 * Draws every object in activeObjects.
	 */
    static void RenderStep();

    //add pointers to game UI, game object, enemy
    static void UIStep(UIManager&);
    static void AddObject(std::shared_ptr<GameObject>);
    static void RemoveObjectFromList(int id);
    static void AddEnemy(std::shared_ptr<Enemy>);

    //generate different types of enemies and checkpoints
    static void GenerateEnemies();
    static void ClearEnemies();
    static void ClearScreen();
    static void ClearCheckpoints();
    static void RestartGame();
    static void HandleCollisions();
    static void StartGame();
    static void ProcessCheckpoint();
    static void updateScore();
    static bool playerMade;

    //declare vectors to screen outputs
    static std::vector<std::shared_ptr<GameObject>> activeObjects;
    static std::shared_ptr<PlayerObject> activePlayer;
    static std::shared_ptr<GameObject> bg1;
    static std::shared_ptr<GameObject> bg2;
    static std::shared_ptr<GameObject> bg3;
    static std::shared_ptr<GameObject> bg4;

    static float backgroundPosition1;
    static float backgroundPosition2;
    static float parallaxPosition1;
    static float parallaxPosition2;

    static std::vector<std::shared_ptr<Enemy>> activeEnemies;
    static std::vector<std::shared_ptr<Checkpoint>> activeCheckpoints;
    static std::vector<std::shared_ptr<UIElement>> activeElements;
    static std::chrono::high_resolution_clock::time_point lastCheckPointTime;
    static double textTimer;
   private:
    static int idGenerator;
    static double playerScore;
    static double scoreMultiplier;

};

#endif /* GAMEMANAGER_H_ */

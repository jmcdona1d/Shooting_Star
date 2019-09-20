/*
 * EnemyManager.h
 *
 *  Created on: Nov. 15, 2018
 *      Author: James Ford
 */

#ifndef ENEMYMANAGER_H_
#define ENEMYMANAGER_H_

const int MIN_SPACE_BETWEEN_WALLS = 128;
const int MOVING_ENEMY_GENERATION_INTERVAL = 1000;
const int MOVING_ENEMY_SIZE = 64;
const int WALL_SIZE = 128;
const int NUM_WALLS = 10;
const float DIFFICULTY_RATE = 0.0001;
const float INITIAL_DIFFICULTY = 2.5;
const float INTERVAL_MOVE = 1000;
const float INTERVAL_WALL = 300;
const float INTERVAL_HOMING = 2000;
const float INTERVAL_CHECKPOINT = 2000;
const float HOMING_MIN_DIFFICULTY = 5;

class EnemyManager {
public:
    static void GenerateMovingEnemy();
    static void GenerateStaticEnemies();
    static void GenerateStaticEnemy();
    static void GenerateCheckpoint();
    static void ClearStaticEnemies();
    static void GenerateHomingEnemy();
    static void Update();
    static void ResetManager();
    static float GetDifficulty();
private:
    static float difficulty;
    static float moveTimer;
    static float wallTimer;
    static float homingTimer;
    static float checkTimer;
};

#endif /* ENEMYMANAGER_H_ */

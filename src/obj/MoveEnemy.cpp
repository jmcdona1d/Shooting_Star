/*
 * GameObject.cpp
 *
 *  Created on: Nov. 3, 2018
 *      Author: ericz
 */

#include "MoveEnemy.h"
#include <iostream>
#include <random>
#include <chrono>
#include "../base/GameRenderer.h"
#include "../base/EnemyManager.h"

using namespace std;

const int MOVEENEMY_SPEED = 0.2;

MoveEnemy::MoveEnemy(double x, double y, int w, int h) : Enemy("MoveEnemy","sprObstacle.png",x, y, w, h) {
    //SetTag("Enemy");
    auto time = chrono::system_clock::to_time_t(chrono::system_clock::now());
    mt19937 mersenneTwister(time);
    std::uniform_int_distribution<> directionGenerator(0, 3);
    std::uniform_int_distribution<> directionGenerator2(0, 3);

    direction = directionGenerator(mersenneTwister);
     switch (direction) {
        case 0:     hspd = -1.5;
                    break;
        case 1:     hspd = 1.5;
                    break;
        case 2:     hspd = -1.5;
                    break;
        case 3:     hspd = 1.5;
                    break;
    }

    direction = directionGenerator2(mersenneTwister);
    vspd = 2;
     switch (direction) {
        case 0:     vspd = 0.6;
                    break;
        case 1:     vspd = 0.8;
                    break;
        case 2:     vspd = 1;
                    break;
        case 3:     vspd = 1.2;
                    break;
    }

}

void MoveEnemy::Logic() {
    Enemy::Logic();

    position[0] += (float)hspd * EnemyManager::GetDifficulty();
    position[1] += (float)vspd * EnemyManager::GetDifficulty();

    if (position[0] <= 0) hspd = -hspd;
    if (position[0] >= GameRenderer::getScreenWidth()) hspd = -hspd;

    if (position[1] > SCREEN_HEIGHT + 150) 
        MarkForDeletion();

}

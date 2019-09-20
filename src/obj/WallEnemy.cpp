/*
 * GameObject.cpp
 *
 *  Created on: Nov. 3, 2018
 *      Author: ericz
 */

#include "WallEnemy.h"
#include "../base/EnemyManager.h"
#include "../base/GameRenderer.h"
#include <iostream>

using namespace std;

WallEnemy::WallEnemy(double x, double y, int w, int h) : Enemy("WallEnemy", "BoxSprite.png", x, y, w, h) {
    //SetTag("Enemy");
}

void WallEnemy::Logic() {
    Enemy::Logic();
    position[1] += 1 * EnemyManager::GetDifficulty();

    if (position[1] > SCREEN_HEIGHT + 150)
        MarkForDeletion();
}

/*
 * HomingEnemy.cpp
 *
 *  Created on: Nov. 19, 2018
 *      Author: Waleed El-Sayed
 */

#include "HomingEnemy.h"
#include <iostream>
#include <random>
#include <chrono>
#include<cmath>
#include "../base/GameRenderer.h"
#include "../base/GameManager.h"
#include "../obj/ExplosionParticle.h"
#include "../base/EnemyManager.h"

using namespace std;

const double HOMINGENEMY_SPEED = 0.075;
extern int FRAME_TIME;
HomingEnemy::HomingEnemy(double x, double y, int w, int h, double l) : Enemy("HomingEnemy","sprHoming.png",x, y, w, h) , lifetime(l) {}

void HomingEnemy::Logic() {
    Enemy::Logic();

    if (GameManager::activePlayer != nullptr) {
        //set so that the velocity is relative to the player
        double normalize = sqrt(pow((GameManager::activePlayer->position[0] - position[0]),2) + pow((GameManager::activePlayer->position[1] - position[1]),2));
        double vx = ((GameManager::activePlayer->position[0] - position[0])/normalize);
        double vy = ((GameManager::activePlayer->position[1] - position[1])/normalize);
        AddForce(vx*HOMINGENEMY_SPEED * EnemyManager::GetDifficulty(), vy*HOMINGENEMY_SPEED * EnemyManager::GetDifficulty());
    }
        //track time so to disappear after FRAME_TIME
    LifetimeTick();
}

//set timer so that when over the lifetime, it disappears
void HomingEnemy::LifetimeTick() {
    lifetime -= FRAME_TIME;
    if (lifetime <= 0) {
        GameManager::AddObject(make_shared<ExplosionParticle>(position[0], position[1]));
        MarkForDeletion();
    }
}
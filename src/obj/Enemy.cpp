/*
 * GameObject.cpp
 *
 *  Created on: Nov. 3, 2018
 *      Author: ericz
 */

#include "Enemy.h"
#include <iostream>
#include <string>

using namespace std;

//constructors for overarching enemy class
Enemy::Enemy(std::string tag, std::string spriteFileName) : GameObject(spriteFileName) {
    SetTag(tag);
}
Enemy::Enemy(std::string tag, std::string spriteFileName, double x, double y, int w, int h) : GameObject(spriteFileName, x, y, w, h) {
    SetTag(tag);
}

void Enemy::Logic() {
    GameObject::Logic();
}

//used to take life here from enemy class but it has been moved to game manager now
void Enemy::DamagePlayer(PlayerObject& player) {
    cout << "TakeLife" << endl;
    //player.TakeLife();
}

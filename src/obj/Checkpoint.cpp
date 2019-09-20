/*
 * GameObject.cpp
 *
 *  Created on: Nov. 3, 2018
 *      Author: ericz
 */

#include "Checkpoint.h"
#include <iostream>

using namespace std;

//constructors for checkpoint with sprite
Checkpoint::Checkpoint() : GameObject("sprCheckpoint.png") {
    SetTag("Checkpoint");
}
Checkpoint::Checkpoint(double x, double y, int w, int h) : GameObject("sprCheckpoint.png", x, y, w, h) {
    SetTag("Checkpoint");
}

//check if the player is on the checkpoint
void Checkpoint::CollidePlayer(PlayerObject& player, int xx, int yy) {
    position[0] = xx;
    position[1] = yy;
    //cout << "Touch Checkpoint" << endl;
}

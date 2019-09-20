#include "PlayerObject.h"
#include "MoveParticle.h"
#include <stdio.h>
#include <cmath>
#define PI 3.14159265

using namespace std;

//constructor methods, one with x and y coordiantes, one without
PlayerObject::PlayerObject() : GameObject("sprPlayer.png"), lives(3), invincible(false), hitCircleSize(20) {
	SetTag("Player");
}
PlayerObject::PlayerObject(double x, double y) : GameObject("sprPlayer.png", x, y, PLAYER_WIDTH, PLAYER_HEIGHT), lives(3), invincible(false), hitCircleSize(20) {
	SetTag("Player");
}

//test if lives are 0 and mark for deletion
void PlayerObject::TakeLife() {
	--lives;
	if (lives == 0)
		MarkForDeletion();
	cout << "lives left: " << lives << endl;
}

//accessor to test if the player can be hit or not
bool PlayerObject::IsInvincible() {
	return invincible;
}

//make the player invincible (can not collide with enemies)
void PlayerObject::TurnInvincible() {
	invincible = true;
}

double PlayerObject::GetHitCircleSize() {
	return hitCircleSize;
}

//test if the player is in the screen window
void PlayerObject::Logic() {
	GameObject::Logic();
	GameManager::AddObject(make_shared<MoveParticle>(position[0], position[1]));

	if (position[0] < 0)
        position[0] = 0;
	if (position[0] > GameRenderer::getScreenWidth())
        position[0] = GameRenderer::getScreenWidth();
	if (position[1] < 0)
        position[1] = 0;
	if (position[1] > GameRenderer::getScreenHeight())
        position[1] = GameRenderer::getScreenHeight();
}

int PlayerObject::GetLives() {return lives;}
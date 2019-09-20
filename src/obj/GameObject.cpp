/*
 * GameObject.cpp
 *
 *  Created on: Oct. 10, 2018
 *      Author: ericz
 */

#include "GameObject.h"
#include "../base/GameRenderer.h"
#include "../base/GameManager.h"

#include <cmath>
#define PI 3.14159265

class GameManager;

using namespace std;

//constructors with one with just the sprite, other with sprite and dimensions
GameObject::GameObject(std::string texturePath) {
	//load sprite
	std::shared_ptr<SDL_Surface> surface(IMG_Load(texturePath.c_str()), SDL_FreeSurface);
	if (surface == nullptr) {
		std::cout << "IMG could not be created! SDL_Error: " << IMG_GetError() << std::endl;
	}
	texture.reset(SDL_CreateTextureFromSurface(GameRenderer::GetRenderer().get(), surface.get()), SDL_DestroyTexture);
	if (texture == nullptr) {
		std::cout << "Texture could not be created! SDL_Error: " << SDL_GetError() << std::endl;
	}

	//set position to 0,0
	position = vector<double>{0, 0};
	velocity = vector<double>{0, 0}; 
	
	//specify width and height
	rect.w = 100;
	rect.h = 100;
	angle = 0;

	UpdateRect();
	WillBeDeleted = false;
}

GameObject::GameObject(std::string texturePath, double x, double y, int w, int h) {
	//load sprite
	std::shared_ptr<SDL_Surface> surface(IMG_Load(texturePath.c_str()), SDL_FreeSurface);
	if (surface == nullptr) {
		std::cout << "IMG could not be created! SDL_Error: " << IMG_GetError() << std::endl;
	}
	texture.reset(SDL_CreateTextureFromSurface(GameRenderer::GetRenderer().get(), surface.get()), SDL_DestroyTexture);
	if (texture == nullptr) {
		std::cout << "Texture could not be created! SDL_Error: " << SDL_GetError() << std::endl;
	}

	//specify position as x,y
	position = vector<double>{x, y};
	velocity = vector<double>{0, 0};

	//specify width and height
	rect.w = w;
	rect.h = h;
    angle = 0;

	UpdateRect();
	WillBeDeleted = false;
}

//accessors
std::shared_ptr<SDL_Texture> GameObject::GetTexture() {
	return texture;
}

SDL_Rect* GameObject::GetRect() {
	return &rect;
}

double GameObject::GetAngle()
{
    return angle;
}

//add a force to the object by adding the x and y component velcoities to the ones before
void GameObject::AddForce(double x, double y) {
		velocity[0] += x;
		velocity[1] += y;
}

//add angular force and apply to components
void GameObject::AddForce2(double spd) {
    double theta = angle * PI / 180.0 ;
    velocity[0] += spd * cos(theta);
    velocity[1] += spd * sin(theta);
}

double GameObject::VelocityMagnitude() {
    return sqrt(velocity[0]*velocity[0] + velocity[1]*velocity[1]);
}

void GameObject::AddRotation(double ang) {
    angle += ang;
}

void GameObject::UpdatePos() {
	position[0] += velocity[0];
	position[1] += velocity[1];

	//create drag so to slow down the object
	velocity[0] *= GLOBAL_DRAG;
	velocity[1] *= GLOBAL_DRAG;
}

void GameObject::UpdateRect() {
	rect.x = position[0] - (rect.w / 2);
	rect.y = position[1] - (rect.h / 2);
}

void GameObject::Logic() {
	UpdatePos();
	UpdateRect();
}

string GameObject::GetTag() {
	return tag;
}

int GameObject::GetID() {
	return id;
}

void GameObject::SetTag(string t) {
	tag = t;
}

void GameObject::SetID(int i) {
	id = i;
}

void GameObject::MarkForDeletion() {
	WillBeDeleted = true;
}

//test to see if in window
bool GameObject::PointInBounds(double x, double y) {
	if (x > rect.x && x < (rect.x + rect.w) &&
		y > rect.y && y < (rect.y + rect.h))
		return true;
	else
		return false;
}

bool GameObject::CircleInBounds(double x, double y, double r) {
	//find x
	double xBox;
	if (x > rect.x && x < (rect.x + rect.w))
		xBox = x;
	else if (x <= rect.x)
		xBox = rect.x;
	else if (x >= (rect.x + rect.w))
		xBox = rect.x + rect.w;

	double yBox;
	if (y > rect.y && y < (rect.y + rect.h))
		yBox = y;
	else if (y <= rect.y)
		yBox = rect.y;
	else if (y >= (rect.y + rect.h))
		yBox = rect.y + rect.h;

	//leaving distances squared instead of finding the root reduces computation time
	double distanceX = x - xBox;
	double distanceY = y - yBox;

	if ((distanceX * distanceX + distanceY * distanceY) < (r * r))
		return true;
	else
		return false;
}

void GameObject::DestroyObject() {
	GameManager::RemoveObjectFromList(id);
}

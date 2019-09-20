/*
 * GameObject.h
 *
 *  Created on: Oct. 10, 2018
 *      Author: ericz
 */

#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include <vector>
#include <memory>
#include <string>

#ifdef _WIN32
	#include "SDL.h"
	#include "SDL_image.h"
#else
	#include "SDL2/SDL.h"
	#include "SDL2/SDL_image.h"
#endif

const double GLOBAL_DRAG = 0.925;

class GameObject {
public:
	GameObject(std::string);
	GameObject(std::string, double, double, int, int);

	std::shared_ptr<SDL_Texture> GetTexture();
	SDL_Rect* GetRect();
	void AddForce(double x, double y);
	void AddForce2(double);
	double VelocityMagnitude();
	void AddRotation(double);
	virtual void Logic();
	void SetTag(std::string);
	void SetID(int);
	std::string GetTag();
	int GetID();
	bool PointInBounds(double, double);
	bool CircleInBounds(double, double, double);
	bool WillBeDeleted;
	void MarkForDeletion();

	void SetActiveObjects(std::vector<std::shared_ptr<GameObject>>&);

	double angle;
	double GetAngle();
	SDL_Point* GetCenter();
	SDL_RendererFlip GetFlip();

	virtual ~GameObject() = default;
	std::vector<double> velocity;
	std::vector<double> position;
private:
	std::shared_ptr<SDL_Texture> texture;
	SDL_Rect rect;
	bool isFixed;
	std::string tag;
	int id;
protected:
	void UpdatePos();
	void UpdateRect();
	void DestroyObject();
	std::vector<std::shared_ptr<GameObject>> activeObjects;
};



#endif /* GAMEOBJECT_H_ */

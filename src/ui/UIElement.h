/*
 * UIElement.h
 *
 *  Created on: Oct. 24, 2018
 *      Author: Eric
 */

#ifndef UI_UIELEMENT_H_
#define UI_UIELEMENT_H_

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

class UIElement {
public:
	UIElement(double, double, int, int);
	UIElement(std::string, double, double, int, int);
	virtual std::shared_ptr<SDL_Texture> GetTexture();
	virtual void Logic() = 0;
	virtual void SetAction(void (*action)()) = 0;
	SDL_Rect* GetRect();
	std::string GetTag();
	void setSize(int, int);
	void SetTag(std::string);
private:
	SDL_Rect bounds;
	std::vector<double> position;
	std::string tag;
protected:
	std::shared_ptr<SDL_Texture> texture;
};



#endif /* UI_UIELEMENT_H_ */

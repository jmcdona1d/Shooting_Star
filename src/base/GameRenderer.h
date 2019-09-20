/*
 * Initialization.h
 *
 *  Created on: Oct. 9, 2018
 *      Author: ericz
 */

#ifndef GAMERENDERER_H_
#define GAMERENDERER_H_

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

#ifdef _WIN32
	#include "SDL.h"
#else
	#include "SDL2/SDL.h"
#endif

#include <stdio.h>
#include <iostream>
#include <memory>
#include <vector>
#include "../obj/GameObject.h"

class GameRenderer{
public:
	static void Initialize();
	static void RenderObjects(std::vector<GameObject>);
	static void UpdateScreen();
	static void ExitGame();
	static std::shared_ptr<SDL_Renderer> GetRenderer();
	static int getScreenWidth();
	static int getScreenHeight();
private:
	static std::shared_ptr<SDL_Window> window;
	static std::shared_ptr<SDL_Surface> surface;
	static std::shared_ptr<SDL_Renderer> renderer;
};



#endif /* GAMERENDERER_H_ */

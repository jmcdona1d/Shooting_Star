/*
 * EventHandler.h
 *
 *  Created on: Oct. 10, 2018
 *      Author: ericz
 */

#ifndef GAMEINPUT_H_
#define GAMEINPUT_H_

#include "GameManager.h"

//set possible status for inputs from user
enum MouseStatus {MOUSEOFF, MOUSEDOWN, MOUSEUP};
enum XDirection {LEFT = -1, XNONE, RIGHT};
enum YDirection {UP = -1, YNONE, DOWN};
enum DirectionAxis {HORIZONTAL, VERTICAL};

class GameInput {
public:
	//constructor
	GameInput();
	void HandleEvent();
	//accessor to user inputs
	static std::vector<int> GetMousePosition();
	static std::vector<int> GetDirectionInput();
	static bool IsMouseDown();
	static bool IsMouseUp();
	//check if game is quitting from player inputs
	static bool IsQuitting();
	static void QuitGame();
private:
	SDL_Event eventHandler;
	//user inputs
	static std::vector<int> mousePosition;
	static std::vector<int> directionInput;
	static bool quit;
	static bool mouseDown;
	static bool mouseUp;
};


#endif /* GAMEINPUT_H_ */

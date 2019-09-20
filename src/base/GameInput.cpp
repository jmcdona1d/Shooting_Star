/*
 * EventHandler.cpp
 *
 *  Created on: Oct. 10, 2018
 *      Author: ericz
 */

#include "GameInput.h"
using namespace std;

//set inputs to false initially
bool GameInput::quit = false;
bool GameInput::mouseDown = false;
bool GameInput::mouseUp = false;
//declare input vectors
vector<int> GameInput::mousePosition;
vector<int> GameInput::directionInput;

GameInput::GameInput() {
	//add inputs to start of vector
	mousePosition.push_back(0);
	mousePosition.push_back(0);
	directionInput.push_back(0);
	directionInput.push_back(0);
}

//use SDL to get events for buttons
void GameInput::HandleEvent() {
	mouseUp = false;
	while (SDL_PollEvent(&eventHandler) != 0) {
		switch (eventHandler.type) {
		case SDL_QUIT:
			GameInput::quit = true;
			break;
		case SDL_MOUSEBUTTONDOWN:
			cout << "mouse down" << endl;
			mouseDown = true;
			break;
		case SDL_MOUSEBUTTONUP:
			cout << "mouse up" << endl;
			mouseDown = false;
			mouseUp = true;
			break;
		}
		/*
		else if (eventHandler.type == SDL_KEYDOWN) {
			switch (eventHandler.key.keysym.sym) {
			case SDLK_w:
				moveObj->AddForce(vector<double>{0, -20});
				cout << "w" << endl;
				break;
			case SDLK_s:
				moveObj->AddForce(vector<double>{0, 20});
				cout << "s" << endl;
				break;
			case SDLK_a:
				moveObj->AddForce(vector<double>{-20, 0});
				cout << "a" << endl;
				break;
			case SDLK_d:
				moveObj->AddForce(vector<double>{20, 0});
				cout << "d" << endl;
				break;
			}
			cout << "new velocity: " << moveObj->velocity[0] << " " << moveObj->velocity[1] << endl;
		}
		*/
	}
	//get keyboard inputs with keys A,S,D,W for movement
	const Uint8* keyState = SDL_GetKeyboardState(NULL);
	if (keyState[SDL_SCANCODE_W])
		directionInput[VERTICAL] = UP;
	else if (keyState[SDL_SCANCODE_S])
		directionInput[VERTICAL] = DOWN;
	else
		directionInput[VERTICAL] = YNONE;

	if (keyState[SDL_SCANCODE_A])
		directionInput[HORIZONTAL] = LEFT;
	else if (keyState[SDL_SCANCODE_D])
		directionInput[HORIZONTAL] = RIGHT;
	else
		directionInput[HORIZONTAL] = XNONE;
	
	//find mouse on window
	SDL_GetMouseState(&mousePosition[0], &mousePosition[1]);
}

//accessor to find key direction
vector<int> GameInput::GetDirectionInput() {
	return directionInput;
}

//accessor to find mouse position
vector<int> GameInput::GetMousePosition() {
	return mousePosition;
}

bool GameInput::IsMouseDown() {
	return mouseDown;
}

bool GameInput::IsMouseUp() {
	return mouseUp;
}

//check to see if game is quitting
bool GameInput::IsQuitting() {
	return GameInput::quit;
}

void GameInput::QuitGame() {
	GameInput::quit = true;
}
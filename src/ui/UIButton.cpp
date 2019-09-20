/*
 * UIButton.cpp
 *
 *  Created on: Oct. 23, 2018
 *      Author: Eric
 */

#include "UIButton.h"
#include "../base/GameRenderer.h"
#include <iostream>
#include "../base/GameInput.h"

using namespace std;

//constructor for button with status as off initially
UIButton::UIButton(std::string texturePath, double x, double y, int w, int h) : UIElement(x, y, w, h),
																			mouseStatus(BUTTONOFF) {
	SetTag("button");

	regSize = {w, h};
	onClickSize = {w + 5, h + 5};
	//set image with texturePath
	std::shared_ptr<SDL_Surface> surface(IMG_Load(texturePath.c_str()), SDL_FreeSurface);
	if (surface == nullptr) {
		std::cout << "IMG could not be created! SDL_Error: " << IMG_GetError() << std::endl;
	}
	image.reset(SDL_CreateTextureFromSurface(GameRenderer::GetRenderer().get(), surface.get()), SDL_DestroyTexture);
	if (image == nullptr) {
		std::cout << "Texture could not be created! SDL_Error: " << SDL_GetError() << std::endl;
	}
}

void UIButton::Logic() {
	vector<int> mousePos = GameInput::GetMousePosition();
	SDL_Rect* rect = GetRect();
	//test to see if over the button
	if (mousePos[0] > rect->x && mousePos[0] < (rect->x + rect->w) &&
			mousePos[1] > rect->y && mousePos[1] < (rect->y + rect->h)){
		setSize(onClickSize[0], onClickSize[1]);
		if (GameInput::IsMouseUp()) {
			buttonAction();
		}
	}
	
	else
		setSize(regSize[0], regSize[1]);
}

void UIButton::SetAction(void (*action)()) {
	buttonAction = action;
}

//accessors to get status of button and button image
void UIButton::ChangeStatus(ButtonStatus status) {
	mouseStatus = status;
}

shared_ptr<SDL_Texture> UIButton::GetTexture() {
	return image;
}


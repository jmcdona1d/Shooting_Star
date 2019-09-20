/*
 * UIText.cpp
 *
 *  Created on: Oct. 23, 2018
 *      Author: Eric
 */

#include "UIText.h"
#include <iostream>
#include "../base/GameRenderer.h"

using namespace std;

UIText::UIText(string t, double x, double y, int s) : UIElement(x, y, 100, 100), text(t) {
	positionx = x;
	positiony = y;
	font.reset(TTF_OpenFont("Righteous-Regular.ttf", s), TTF_CloseFont);
	if (font == nullptr)
		cout << "font was not initialized! SDL_ttf Error: " << TTF_GetError() << endl;
	else {
		textColor = {255, 255, 0};
	}

	TTF_SizeText(font.get(), t.c_str(), &GetRect()->w, &GetRect()->h);
	GetRect()->x = positionx - (GetRect()->w / 2);
	GetRect()->y = positiony - (GetRect()->h / 2);

	SetTag("text");
	shared_ptr<SDL_Surface> surface(TTF_RenderText_Solid(font.get(), text.c_str(), textColor), SDL_FreeSurface);
	if (surface == nullptr) {
		cout << "IMG could not be created! SDL_Error: " << IMG_GetError() << endl;
	}
	texture.reset(SDL_CreateTextureFromSurface(GameRenderer::GetRenderer().get(), surface.get()), SDL_DestroyTexture);
	if (texture == nullptr) {
		cout << "Texture could not be created! SDL_Error: " << SDL_GetError() << endl;
	}
}

void UIText::Logic() {
}

std::string UIText::getText(){
	return text;
}

void UIText::SetAction(void (*action)()) {
}

void UIText::ChangeText(std::string t) {
	text = t;
	TTF_SizeText(font.get(), t.c_str(), &GetRect()->w, &GetRect()->h);
	GetRect()->x = positionx - (GetRect()->w / 2);
	GetRect()->y = positiony - (GetRect()->h / 2);
	shared_ptr<SDL_Surface> surface(TTF_RenderText_Solid(font.get(), text.c_str(), textColor), SDL_FreeSurface);
	if (surface == nullptr) {
		cout << "IMG could not be created! SDL_Error: " << IMG_GetError() << endl;
	}
	texture.reset(SDL_CreateTextureFromSurface(GameRenderer::GetRenderer().get(), surface.get()), SDL_DestroyTexture);
	if (texture == nullptr) {
		cout << "Texture could not be created! SDL_Error: " << SDL_GetError() << endl;
	}
}

void UIText::UpdatePosition(double x, double y) {
	positionx = x;
	positiony = y;
	TTF_SizeText(font.get(), text.c_str(), &GetRect()->w, &GetRect()->h);
	GetRect()->x = positionx - (GetRect()->w / 2);
	GetRect()->y = positiony - (GetRect()->h / 2);
	shared_ptr<SDL_Surface> surface(TTF_RenderText_Solid(font.get(), text.c_str(), textColor), SDL_FreeSurface);
	if (surface == nullptr) {
		cout << "IMG could not be created! SDL_Error: " << IMG_GetError() << endl;
	}
	texture.reset(SDL_CreateTextureFromSurface(GameRenderer::GetRenderer().get(), surface.get()), SDL_DestroyTexture);
	if (texture == nullptr) {
		cout << "Texture could not be created! SDL_Error: " << SDL_GetError() << endl;
	}
}
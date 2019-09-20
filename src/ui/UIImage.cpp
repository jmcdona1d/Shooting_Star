/*
 * UIImage.cpp
 *
 *  Created on: Oct. 23, 2018
 *      Author: Eric
 */

#include "UIImage.h"
#include <iostream>
#include "../base/GameRenderer.h"

using namespace std;

//Build the image constructor with including the dimensions and the sprite name
UIImage::UIImage(string imagePath, double x, double y, int w, int h) : UIElement(x, y, w, h) {
	SetTag("image");
	//load image
	std::shared_ptr<SDL_Surface> surface(IMG_Load(imagePath.c_str()), SDL_FreeSurface);
	if (surface == nullptr) {
		cout << "IMG could not be created! SDL_Error: " << IMG_GetError() << endl;
	}
	image.reset(SDL_CreateTextureFromSurface(GameRenderer::GetRenderer().get(), surface.get()), SDL_DestroyTexture);
	if (image == nullptr) {
		cout << "Texture could not be created! SDL_Error: " << SDL_GetError() << endl;
	}
}

shared_ptr<SDL_Texture> UIImage::GetTexture() {
	return image;
}

void UIImage::Logic() {
}

void UIImage::SetAction(void (*action)()) {
}

/*
 * UIElement.cpp
 *
 *  Created on: Oct. 24, 2018
 *      Author: Eric
 */

#include "UIElement.h"
#include <iostream>
#include "../base/GameRenderer.h"


using namespace std;
//constructor with placement and dimensions
UIElement::UIElement(double x, double y, int w, int h) {
	position = vector<double>{x, y};

	bounds.x = position[0];
	bounds.y = position[1];
	bounds.w = w;
	bounds.h = h;
}

void UIElement::setSize(int w, int h){
	bounds.w = w;
	bounds.h = h;
}

void UIElement::SetTag(string t) {
	tag = t;
}

//accesors to get variables from UIElement
string UIElement::GetTag() {
	return tag;
}

SDL_Rect* UIElement::GetRect() {
	return &bounds;
}

shared_ptr<SDL_Texture> UIElement::GetTexture() {
	return texture;
}
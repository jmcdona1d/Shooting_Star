/*
 * UIText.h
 *
 *  Created on: Oct. 23, 2018
 *      Author: Eric
 */

#ifndef UI_UITEXT_H_
#define UI_UITEXT_H_

#include "UIElement.h"

#ifdef _WIN32 
	#include "SDL_ttf.h"
#else
	#include "SDL2/SDL_ttf.h"
#endif

class UIText : public UIElement {
public:
	UIText(std::string, double, double, int);
	void ChangeText(std::string);
	virtual void Logic() override;
	virtual void SetAction(void (*action)()) override;
	void UpdatePosition(double, double);
	std::string getText();
	double positionx;
	double positiony;
private:
	std::shared_ptr<TTF_Font> font;
	std::string text;
	SDL_Color textColor;

};




#endif /* UI_UITEXT_H_ */

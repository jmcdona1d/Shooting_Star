/*
 * UIButton.h
 *
 *  Created on: Oct. 23, 2018
 *      Author: Eric
 */

#ifndef UI_UIBUTTON_H_
#define UI_UIBUTTON_H_

#include "UIElement.h"
#include <iostream>

enum ButtonStatus {BUTTONOFF, BUTTONOVER, BUTTONDOWN};

class UIButton : public UIElement{
public:
	UIButton(std::string, double, double, int, int);
	virtual std::shared_ptr<SDL_Texture> GetTexture() override;
	virtual void Logic() override;
	void ChangeStatus(ButtonStatus);
	virtual void SetAction(void (*action)()) override;
private:
	std::shared_ptr<SDL_Texture> image;
	void (*buttonAction)();
	int mouseStatus;
	std::vector<int> regSize;
	std::vector<int> onClickSize;
};



#endif /* UI_UIBUTTON_H_ */

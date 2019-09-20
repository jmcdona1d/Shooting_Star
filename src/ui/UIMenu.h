/*
 * UIMenu.h
 *
 *  Created on: Oct. 23, 2018
 *      Author: Eric
 */

#ifndef UI_UIMENU_H_
#define UI_UIMENU_H_

#include <vector>
#include <string>
#include <iostream>
#include "UIButton.h"
#include "UIImage.h"

class UIMenu {
public:
	UIMenu(std::string);
	std::vector<std::shared_ptr<UIElement>> elementList;
	std::vector<std::shared_ptr<UIButton>> buttonList;
	std::string GetTitle();
private:
	std::string title;

};



#endif /* UI_UIMENU_H_ */

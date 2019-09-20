/*
 * UIMenu.cpp
 *
 *  Created on: Oct. 23, 2018
 *      Author: Eric
 */

#include "UIMenu.h"

using namespace std;

UIMenu::UIMenu(string t) : title(t) {}

string UIMenu::GetTitle() {
	return title;
}

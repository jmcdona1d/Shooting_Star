/*
 * UIImage.h
 *
 *  Created on: Oct. 23, 2018
 *      Author: Eric
 */

#ifndef UI_UIIMAGE_H_
#define UI_UIIMAGE_H_

#include "UIElement.h"

class UIImage : public UIElement {
public:
	UIImage(std::string, double, double, int, int);
	virtual std::shared_ptr<SDL_Texture> GetTexture() override;
	virtual void Logic() override;
	virtual void SetAction(void (*action)()) override;
private:
	std::shared_ptr<SDL_Texture> image;

};




#endif /* UI_UIIMAGE_H_ */

/*
 * UIManager.h
 *
 *  Created on: Oct. 23, 2018
 *      Author: Eric
 */

#ifndef BASE_UIMANAGER_H_
#define BASE_UIMANAGER_H_

#include <vector>
#include <iostream>
#include "../base/GameRenderer.h"
#include "UIMenu.h"
#include "UIText.h"
#ifdef _WIN32
	#include "SDL_image.h"
#else
	#include "SDL2/SDL_image.h"
#endif

enum MenuState {MAIN, QUITGAME, INGAME};

class UIManager {
public:
	UIManager();
	static void ChangeState(MenuState);
	void InitializeMenus();
	UIMenu CurrentMenu();
	void Logic();

	static void Play();
	static void Quit();
	static void Filler();
	static void End();
	static void Replay();

	MenuState getMenuState();
	void AddElement(std::shared_ptr<UIElement>, MenuState);
	void AddElement(std::shared_ptr<UIElement>, MenuState, void (*action)());
	std::shared_ptr<SDL_Texture> GetTexture();
	static std::shared_ptr<UIText> scoreText;
	static std::shared_ptr<UIText> finalScoreText;
	static std::shared_ptr<UIText> livesText;
	static std::shared_ptr<UIText> getPointsText;
	static double getPointsVelocity;
private:
	static MenuState menuState;
	std::vector<UIMenu> menus;
	std::shared_ptr<SDL_Texture> texture;


};



#endif /* BASE_UIMANAGER_H_ */

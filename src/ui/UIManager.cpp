/*
 * UIManager.cpp
 *
 *  Created on: Oct. 23, 2018
 *      Author: Eric
 */

#include "UIManager.h"
#include "../base/GameInput.h"
#ifdef _WIN32
	#include "SDL_image.h"
#else
	#include "SDL2/SDL_image.h"
#endif

using namespace std;

//set menu state for main menu
MenuState UIManager::menuState = MenuState::MAIN;

//set UIText pointers
shared_ptr<UIText> UIManager::scoreText;
shared_ptr<UIText> UIManager::finalScoreText;
shared_ptr<UIText> UIManager::livesText;
shared_ptr<UIText> UIManager::getPointsText;
double UIManager::getPointsVelocity = 0;

UIManager::UIManager() {
	InitializeMenus();
}

//return current menu state
UIMenu UIManager::CurrentMenu() {
	return menus[menuState];
}

//change menu state (will create new menu for main, ingame, or quitgame)
void UIManager::ChangeState(MenuState state) {
	menuState = state;
}

//add elements (for buttons in menus) without action
void UIManager::AddElement(shared_ptr<UIElement> element, MenuState menu) {
	menus.at(menu).elementList.push_back(element);
	if (element->GetTag() == "button") {
		menus.at(menu).buttonList.push_back(dynamic_pointer_cast<UIButton>(element));
	}
}

//add elements (for buttons in menus) with action
void UIManager::AddElement(shared_ptr<UIElement> element, MenuState menu, void (*action)()) {
	menus.at(menu).elementList.push_back(element);
	if (element->GetTag() == "button") {
		menus.at(menu).buttonList.push_back(dynamic_pointer_cast<UIButton>(element));
		element->SetAction(action);
	}
}

void UIManager::InitializeMenus() {
	//main menu
	menus.push_back(UIMenu("Main Menu"));
	//load image/element for play button 
	AddElement(make_shared<UIButton>("Play.png", (SCREEN_WIDTH / 2) - 100, 100, 200, 100), MenuState::MAIN, UIManager::Play);
	//load image/element for quit button 	
	AddElement(make_shared<UIButton>("Quit.png", (SCREEN_WIDTH / 2) - 100, 400, 200, 100), MenuState::MAIN, UIManager::Quit);

	//Quit Menu
	menus.push_back(UIMenu("Quit"));
	
	//load image/element for game over 
	AddElement(make_shared<UIImage>("GameOver.png", (SCREEN_WIDTH / 2) - 175, 60, 350, 150), MenuState::QUITGAME);
	UIManager::finalScoreText = make_shared<UIText>("Score: 0", (SCREEN_WIDTH / 2), 200, 50);
	//add in final score
	AddElement(finalScoreText, MenuState::QUITGAME);
	//load image/element for replay button 
	AddElement(make_shared<UIButton>("Replay.png", (SCREEN_WIDTH / 2) - 100, 300, 200, 100), MenuState::QUITGAME, UIManager::Replay);
	//load image/element for quit button
	AddElement(make_shared<UIButton>("Quit.png", (SCREEN_WIDTH / 2) - 100, 450, 200, 100), MenuState::QUITGAME, UIManager::Quit);


	//In game Menu
	menus.push_back(UIMenu("Play"));
	//set text to display lives
	UIManager::livesText = make_shared<UIText>("Lives:", (SCREEN_WIDTH * 0.4), SCREEN_HEIGHT - 20, 32);
	AddElement(livesText, MenuState::INGAME);
	//set text to display score
	UIManager::scoreText = make_shared<UIText>("Score:", (SCREEN_WIDTH * 0.6), SCREEN_HEIGHT - 20, 32);
	AddElement(scoreText, MenuState::INGAME);
	UIManager::getPointsText = make_shared<UIText>("Test", SCREEN_WIDTH * 0.5, SCREEN_HEIGHT * 0.5, 24);
	AddElement(getPointsText, MenuState::INGAME);

	//interaction with mouse input
	menus[MenuState::MAIN].buttonList.push_back(dynamic_pointer_cast<UIButton>(menus[0].elementList[0]));
	menus[MenuState::MAIN].buttonList.push_back(dynamic_pointer_cast<UIButton>(menus[0].elementList[1]));

	menus[MenuState::QUITGAME].buttonList.push_back(dynamic_pointer_cast<UIButton>(menus[1].elementList[0]));
	menus[MenuState::QUITGAME].buttonList.push_back(dynamic_pointer_cast<UIButton>(menus[1].elementList[1]));
}

//function to play game
void UIManager::Play() {
	cout << "play game" << endl;
	//move to ingame state
	ChangeState(MenuState::INGAME);
}

//function to quit the game
void UIManager::Quit() {
	GameInput::QuitGame();
	cout<<"quit game"<<endl;	
}

//function to replay (reset game)
void UIManager::Replay() {
	cout << "replay game" << endl;
	GameManager::RestartGame();
	ChangeState(MenuState::INGAME);
}

//test function
void UIManager::Filler() {
	cout << "filler" << endl;
}

//funtion to force menustate to end
void UIManager::End() {
	ChangeState(MenuState::QUITGAME);
}

MenuState UIManager::getMenuState(){
	return UIManager::menuState;
}

void UIManager::Logic() {
	for (auto &element : menus[menuState].elementList) {
		element->Logic();
	}
}

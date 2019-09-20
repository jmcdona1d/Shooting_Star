#include "GameRenderer.h"

#ifdef _WIN32 
	#include "SDL_image.h"
	#include "SDL_ttf.h"
#else
	#include "SDL2/SDL_image.h"
	#include "SDL2/SDL_ttf.h"
#endif

using namespace std;

//delcare global pointers
shared_ptr<SDL_Window> GameRenderer::window(NULL, SDL_DestroyWindow);
shared_ptr<SDL_Surface> GameRenderer::surface(NULL, SDL_FreeSurface);
shared_ptr<SDL_Renderer> GameRenderer::renderer(NULL, SDL_DestroyRenderer);

void GameRenderer::Initialize() {
	//test if SDL is initialized
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL could not be initialized! SDL_Error: " << SDL_GetError() << endl;
	}
	//test if window and renderer can be initialized if so, render all
	else
	{
		window.reset(SDL_CreateWindow( "Shooting Star", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN ), SDL_DestroyWindow);
		if (window == NULL)
		{
			cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
		}
		else
		{
			SDL_SetWindowSize(window.get(), SCREEN_WIDTH, SCREEN_HEIGHT);
			renderer.reset(SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC), SDL_DestroyRenderer);
			if (renderer == nullptr) {
				cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << endl;
			}
			else {
				//build black screen window
				SDL_SetRenderDrawColor(renderer.get(), 0x00, 0x00, 0x00, 0xFF);
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) ) {
					printf( "SDL_image could not be initialized! SDL_image Error: %s\n", IMG_GetError() );
				}
				if (TTF_Init() == -1) {
					printf( "SDL_ttf could not be initialized! SDL_ttf Error: %s\n", TTF_GetError() );
				}
			}
		}
	}

}

void GameRenderer::RenderObjects(vector<GameObject>) {
	SDL_RenderClear(GameRenderer::GetRenderer().get());
}

//accesors to get screen dimensions
int GameRenderer::getScreenWidth(){
	return SCREEN_WIDTH;
}
int GameRenderer::getScreenHeight(){
	return SCREEN_HEIGHT;
}

std::shared_ptr<SDL_Renderer> GameRenderer::GetRenderer() {
	return renderer;
}



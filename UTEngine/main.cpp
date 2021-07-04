#include "SDL.h"
#include "Game.h"
#include <iostream>

#undef main //Wtf does this even do lmao

int main(int argc, char* argv[])
{
	/*SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("UNDERTALE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
	
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

	SDL_RenderClear(renderer);

	SDL_RenderPresent(renderer);

	SDL_Delay(3000);*/

	Game* game = new Game();

	game->init("UNDERTALE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, false);

	while(game->running())
	{
		game->handleEvents();
		game->update();
		game->render();
	}

	//Master

	game->clean();

	return 0;
}
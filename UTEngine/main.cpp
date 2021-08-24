#include "SDL.h"
#include "Game.h"
#include <iostream>

#define FPS 30
#define FDELAY 1000/FPS

#undef main

int deltaTime = 0;

int main(int argc, char* argv[])
{
	Uint32 frameStart;
	Game* game = new Game();
	game->init("UNDERTALE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, false, "room_ruinstest.json");

	while(game->running())
	{
		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();
		game->endFrame();

		deltaTime = SDL_GetTicks() - frameStart;

		if (deltaTime < FDELAY)
		{
			SDL_Delay(FDELAY - deltaTime);
		}
	}

	game->clean();

	return 0;
}
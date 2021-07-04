#include "SDL.h"
#include "Game.h"
#include <iostream>

#define FPS 30
#define FDELAY 1000/FPS

#undef main

int main(int argc, char* argv[])
{
	Uint32 frameStart;
	int frameTime;

	Game* game = new Game();

	game->init("UNDERTALE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, false);

	while(game->running())
	{
		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameTime < FDELAY)
		{
			SDL_Delay(FDELAY - frameTime);
		}
	}

	game->clean();

	return 0;
}
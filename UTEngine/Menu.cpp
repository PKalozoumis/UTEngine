#include "Menu.h"
#include "functions.h"
#include "Game.h"
#include "SDL.h"
void Menu::switchState(void)
{
	if ((SDL_GetWindowFlags(Game::window)&SDL_WINDOW_FULLSCREEN_DESKTOP) == 0)
	{
		SDL_SetWindowFullscreen(Game::window, SDL_WINDOW_FULLSCREEN_DESKTOP);
	}
	else  SDL_SetWindowFullscreen(Game::window, 0);
}

bool Menu::isActive(void) const
{
	return active;
}

void Menu::draw(void) const
{
	if(active)
	{
		drawMenuBox(6,6,150,100);
	}
}
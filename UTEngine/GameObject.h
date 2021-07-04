#pragma once

#include "Game.h"

class GameObject
{
	public:
		GameObject(const char* textureSheet, SDL_Renderer* renderer, int x = 0, int y = 0);

		void update();
		void render();
		int getX();
		int getY();

	private:
		int x;
		int y;

		SDL_Texture* objSprite;
		SDL_Rect srcRect, destRect;
		SDL_Renderer* renderer;

};


#pragma once

#include "Game.h"
#include <iostream>

class TextureManager
{
	public:
		static SDL_Texture* loadTexture(std::string directory);
		static void draw(SDL_Texture* texture, SDL_Rect source, SDL_Rect destination);
};
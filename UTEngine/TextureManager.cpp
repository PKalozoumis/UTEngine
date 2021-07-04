#include "TextureManager.h"
#include <iostream>

SDL_Texture* TextureManager::loadTexture(const char* directory, SDL_Renderer* renderer)
{
	SDL_Surface* tempSurface = IMG_Load(directory);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	return texture;
}
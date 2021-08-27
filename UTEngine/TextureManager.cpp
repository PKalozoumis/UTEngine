#include "TextureManager.h"
#include <iostream>
#include "Game.h"

SDL_Texture* TextureManager::loadTexture(std::string directory)
{
	SDL_Surface* tempSurface = IMG_Load(directory.c_str());
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	return texture;
}

void TextureManager::draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest)
{
	SDL_RenderCopy(Game::renderer, tex, &src, &dest);
}
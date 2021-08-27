#include "Sprite.h"
#include <iostream>
#include "TextureManager.h"
#include "Game.h"

Sprite::Sprite(std::string directory)
{
	texture = TextureManager::loadTexture(directory);

	SDL_QueryTexture(texture, NULL, NULL, &imageWidth, &imageHeight);

	name = directory.substr(directory.find_last_of('/') + 1, directory.find_last_of('.') - directory.find_last_of('/') - 1);
}

Sprite::Sprite(const Sprite& other)
{
	this->texture = other.texture;
	this->imageHeight = other.imageHeight;
	this->imageWidth = other.imageWidth;
	this->name = other.name;
}

int Sprite::getImageWidth(void) const
{
	return imageWidth;
}

int Sprite::getImageHeight(void) const
{
	return imageHeight;
}

SDL_Texture* Sprite::getTexture(void) const
{
	return texture;
}

void Sprite::draw(int x, int y) const
{
	SDL_Rect rect = {x,y,imageWidth, imageHeight};
	SDL_RenderCopy(Game::renderer, texture, NULL, &rect);
}

void Sprite::operator=(const Sprite& otherSprite)
{
	this->texture = otherSprite.texture;
	this->imageHeight = otherSprite.imageHeight;
	this->imageWidth = otherSprite.imageWidth;
	this->name = otherSprite.name;
}

std::string Sprite::getName(void) const
{
	return name;
}

void Sprite::setTexture(std::string directory)
{
	SDL_DestroyTexture(texture);

	texture = TextureManager::loadTexture(directory);

	SDL_QueryTexture(texture, NULL, NULL, &imageWidth, &imageHeight);

	name = directory.substr(directory.find_last_of('/') + 1, directory.find_last_of('.') - directory.find_last_of('/') - 1);
}

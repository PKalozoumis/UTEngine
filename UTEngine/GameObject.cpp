#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char* textureSheet, SDL_Renderer* renderer, int x, int y)
{
	this->renderer = renderer;
	this->x = x;
	this->y = y;
	objSprite = TextureManager::loadTexture(textureSheet, renderer);
}

void GameObject::update()
{
	srcRect.w = 19;
	srcRect.h = 29;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = x;
	destRect.y = y;
	destRect.w = srcRect.w * 2;
	destRect.h = srcRect.h * 2;
}

void GameObject::render()
{
	SDL_RenderCopy(renderer, objSprite, &srcRect, &destRect);
}

int GameObject::getX()
{
	return x;
}

int GameObject::getY()
{
	return y;
}

void GameObject::addX(int x)
{
	this->x += x;
}

void GameObject::addY(int y)
{
	this->y += y;
}
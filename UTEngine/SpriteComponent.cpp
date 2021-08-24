#include "SpriteComponent.h"
#include "TextureManager.h"
#include <iostream>

void SpriteComponent::init(void)
{
	transform = &entity->getComponent<TransformComponent>();

	srcRect.x = srcRect.y = 0;
	SDL_QueryTexture(texture, NULL, NULL, &srcRect.w, &srcRect.h);

	imageWidth = srcRect.w;
	imageHeight = srcRect.h;

	destRect.x = transform->getX();
	destRect.y = transform->getY();
	destRect.w = imageWidth*transform->getXscale();
	destRect.h = imageHeight*transform->getYscale();

	transform->setWidth(imageWidth);
	transform->setHeight(imageHeight);
}

void SpriteComponent::update(void)
{
	int xalign, yalign;

	srcRect.x = srcRect.y = 0;
	SDL_QueryTexture(texture, NULL, NULL, &srcRect.w, &srcRect.h);

	imageWidth = srcRect.w;
	imageHeight = srcRect.h;

	destRect.w = imageWidth*transform->getXscale();
	destRect.h = imageHeight*transform->getYscale();

	switch(halign)
	{
		case left: xalign = 0; break;
		case right: xalign = -destRect.w; break;
		case xcenter: xalign = -static_cast<int>(destRect.w/2); break;
	}

	switch(valign)
	{
		case top: yalign = 0; break;
		case bottom: yalign = -destRect.h; break;
		case ycenter: yalign = -static_cast<int>(destRect.h/2); break;
	}

	if ((transform->getX() >= Game::xbor) && (transform->getX() <= Game::camera.w -  Game::xbor))
	{
		destRect.x = Game::xbor + xalign;
	}
	else destRect.x = transform->getX() - Game::camera.x + xalign;

	if ((transform->getY() >= Game::ybor) && (transform->getY() <= Game::camera.h -  Game::ybor))
	{
		destRect.y = Game::ybor + yalign;
	}
	else destRect.y = transform->getY() - Game::camera.y + yalign;

	transform->setWidth(imageWidth);
	transform->setHeight(imageHeight);
}

void SpriteComponent::draw(void)
{
	TextureManager::draw(texture, srcRect, destRect);
}

SpriteComponent::SpriteComponent(std::string directory, HorizontalAlign halign, VerticalAlign valign)
{
	texture = TextureManager::loadTexture(directory);
	this->halign = halign;
	this->valign = valign;
}

/*SpriteComponent::~SpriteComponent(void)
{
	SDL_DestroyTexture(texture);
}*/

void SpriteComponent::setSprite(std::string directory)
{
	texture = TextureManager::loadTexture(directory);
}

SDL_Texture* SpriteComponent::getSprite(void) const
{
	return texture;
}

int SpriteComponent::getImageIndex(void) const
{
	int moveTime = transform->getMoveTime();

	return (moveTime/(30/imageSpeed))%numberOfFrames;
}

int SpriteComponent::getImageWidth(void) const
{
	return imageWidth;
}

int SpriteComponent::getImageHeight(void) const
{
	return imageHeight;
}

void SpriteComponent::setHalign(HorizontalAlign align)
{
	halign = align;
}

void SpriteComponent::setValign(VerticalAlign align)
{
	valign = align;
}
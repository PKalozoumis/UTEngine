#pragma once
#include "ECS.h"
#include "SDL.h"
#include "TransformComponent.h"
#include <iostream>

enum HorizontalAlign
{
	left,
	right,
	xcenter
};

enum VerticalAlign
{
	top,
	bottom,
	ycenter
};

class SpriteComponent : public Component
{
	private:
		TransformComponent* transform;
		SDL_Texture* texture;
		SDL_Rect srcRect, destRect;
		int imageSpeed = 6; //6
		int imageIndex;
		int numberOfFrames = 4;
		HorizontalAlign halign;
		VerticalAlign valign;
		int imageWidth, imageHeight;

	public:
		SpriteComponent() = default;
		//~SpriteComponent(void);
		SpriteComponent(std::string path, HorizontalAlign halign = left, VerticalAlign valign = top);

		void init(void);
		void update(void);
		void draw(void);
		int getImageIndex(void) const;

		int getImageWidth(void) const;
		int getImageHeight(void) const;

		void setHalign(HorizontalAlign align);
		void setValign(VerticalAlign align);

		void setSprite(std::string directory);
		SDL_Texture* getSprite(void) const;
};


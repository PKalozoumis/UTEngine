#pragma once
#include "Vec2.h"
#include "SDL.h"
#include <iostream>

class Sprite
{
	private:
		int imageWidth, imageHeight;
		SDL_Texture* texture;
		std::string name;
			
	public:
		int getImageWidth(void) const;
		int getImageHeight(void) const;
		SDL_Texture* getTexture(void) const;

		void draw(int x, int y) const;

		std::string getName(void) const;
		void setTexture(std::string directory);

		Sprite(std::string directory = "");
		Sprite(const Sprite& other);

		void operator=(const Sprite& otherSprite);
};


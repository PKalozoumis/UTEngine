#pragma once
#include "Button.h"
#include "Sprite.h"

class SpriteButton : public Button
{
	private:
		Sprite sprite, spriteNormal, spriteHover, spritePressed;

	public:
		SpriteButton(std::string directory, int x = 0, int y = 0);
		SpriteButton(Sprite sprite, int x = 0, int y = 0);

		void setSprite(Sprite sprite);
		void draw(void);
		void update(void);
};


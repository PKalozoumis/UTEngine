#pragma once
#include "Button.h"
#include "Sprite.h"

class SpriteButton : public Button
{
	private:
		Sprite sprite, spriteNormal, spriteHover, spritePressed;

	public:
		SpriteButton(std::string directory, std::string label = "", std::string message = "", int x = 0, int y = 0);
		SpriteButton(Sprite sprite, std::string label = "", std::string message = "", int x = 0, int y = 0);

		void setSprite(Sprite sprite);
		void draw(void) const;
		void update(void);
};


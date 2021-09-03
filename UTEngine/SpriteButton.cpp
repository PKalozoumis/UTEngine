#include "SpriteButton.h"
#include "Sprite.h"
#include "SDL.h"

SpriteButton::SpriteButton(std::string directory, std::string label, std::string message, int x, int y):Button(label,message,x,y)
{
	sprite = Sprite(directory);
	spriteNormal = sprite;
	spriteHover = Sprite("assets/sprites/debug/" + sprite.getName() + "Hover.png");
	spritePressed = Sprite("assets/sprites/debug/" + sprite.getName() + "Pressed.png"),

	SDL_QueryTexture(sprite.getTexture(), nullptr, nullptr, &pos.w, &pos.h);
}

SpriteButton::SpriteButton(Sprite sprite, std::string label, std::string message, int x, int y):Button(label,message,x,y)
{
	this->sprite = sprite;
	spriteNormal = sprite;
	spriteHover = Sprite("assets/sprites/debug/" + sprite.getName() + "Hover.png");
	spritePressed = Sprite("assets/sprites/debug/" + sprite.getName() + "Pressed.png"),

	SDL_QueryTexture(sprite.getTexture(), nullptr, nullptr, &pos.w, &pos.h);
}

void SpriteButton::draw(void) const
{
	sprite.draw(pos.x, pos.y);
	Button::draw();
}

void SpriteButton::update(void)
{
	Button::update();

	if (boolMouseInArea)
	{
		if (pressed)
		{
			sprite = spritePressed;
		}
		else sprite = spriteHover;
	}
	else sprite = spriteNormal;
}

void SpriteButton::setSprite(Sprite sprite)
{
	this->sprite = sprite;
}
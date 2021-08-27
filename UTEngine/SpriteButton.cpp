#include "SpriteButton.h"
#include "Sprite.h"
#include "SDL.h"

SpriteButton::SpriteButton(std::string directory, int x, int y):Button(x,y)
{
	sprite = Sprite(directory);
	spriteNormal = sprite;
	spriteHover = Sprite("assets/sprites/debug/" + sprite.getName() + "Hover.png");
	spritePressed = Sprite("assets/sprites/debug/" + sprite.getName() + "Pressed.png"),
	
	//spriteHover.setTexture("assets/sprites/debug/" + name + "Hover.png");

	SDL_QueryTexture(sprite.getTexture(), nullptr, nullptr, &border.w, &border.h);

	border.w *= 2;
	border.h *= 2;
}

SpriteButton::SpriteButton(Sprite sprite, int x, int y):Button(x,y)
{
	this->sprite = sprite;
	spriteNormal = sprite;
	spriteHover = Sprite("assets/sprites/debug/" + sprite.getName() + "Hover.png");
	spritePressed = Sprite("assets/sprites/debug/" + sprite.getName() + "Pressed.png"),
	
	//spriteHover.setTexture("assets/sprites/debug/" + name + "Hover.png");

	SDL_QueryTexture(sprite.getTexture(), nullptr, nullptr, &border.w, &border.h);

	border.w *= 2;
	border.h *= 2;
}

void SpriteButton::draw(void)
{
	sprite.draw(border.x, border.y);
	Button::draw();
}

void SpriteButton::update(void)
{
	Button::update();

	if (mouseOnButton)
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
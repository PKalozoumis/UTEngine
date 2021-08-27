#include "Button.h"
#include "functions.h"
#include "Game.h"
#include <iostream>
#include "Mouse.h"
#include "TextureManager.h"
#include "Debug.h"

Button::Button(int x, int y, int w, int h)
{
	border.x = x;
	border.y = y;
	border.w = w;
	border.h = h;
}

void Button::update(void)
{
	if ((withinRange(Mouse::getViewX(), border.x*2, border.x*2 + border.w))&&(withinRange(Mouse::getViewY(), border.y*2, border.y*2 + border.h)))
	{
		mouseOnButton = true;
	}
	else mouseOnButton = false;

	if (mouseOnButton && Mouse::buttonPressed(SDL_BUTTON_LMASK))
	{
		pressed = true;
	}
	else pressed = false;
}

void Button::draw(void)
{
	if (Debug::boolButtonHitboxes)
	{
		drawSetColor(c_lime);
		SDL_Rect tempBorder = border;
		tempBorder.w/=2;
		tempBorder.h/=2;
		SDL_RenderDrawRect(Game::renderer, &tempBorder);
		drawResetColor();
	}
}

bool Button::checkMouseOnButton(void) const
{
	return mouseOnButton;
}

void Button::setHeight(int height)
{
	border.h = height;
}

void Button::setWidth(int width)
{
	border.w = width;
}

void Button::setBorder(SDL_Rect rect)
{
	border = rect;
}

bool Button::isPressed(void)
{
	return pressed;
}
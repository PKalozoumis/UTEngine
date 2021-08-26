#include "Button.h"
#include "functions.h"
#include "Game.h"
#include <iostream>
#include "Mouse.h"

Button::Button(int x, int y, int w, int h)
{
	border.x = x;
	border.y = y;
	border.w = w;
	border.h = h;
}

void Button::update(void)
{
	if ((withinRange(Mouse::getViewX(), border.x, border.x + border.w))&&(withinRange(Mouse::getViewY(), border.y, border.y + border.h)))
	{
		mouseOnButton = true;
	}
	else mouseOnButton = false;
}

void Button::draw(void)
{
	drawSetColor(c_lime);
	SDL_Rect tempBorder = border;
	tempBorder.x/=2;
	tempBorder.y/=2;
	tempBorder.w/=2;
	tempBorder.h/=2;
	SDL_RenderDrawRect(Game::renderer, &tempBorder);
	drawResetColor();
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
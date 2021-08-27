#include "Button.h"
#include "functions.h"
#include "Game.h"
#include <iostream>
#include "Mouse.h"
#include "TextureManager.h"
#include "Debug.h"
#include "functions.h"

Button::Button(std::string label, std::string message, int x, int y, int w, int h)
{
	border.x = x;
	border.y = y;
	border.w = w;
	border.h = h;
	this->label = label;
	this->message = message;
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

	if (pressed)
	{
		Debug::addMessage(message);
	}
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

	int labelWidth = label.length()*4.5;

	int x1 = Mouse::getViewX()/2;
	int y1 = Mouse::getViewY()/2;

	if (mouseOnButton && (label != ""))
	{
		if (x1 + labelWidth >= 320)
		{
			x1 -= labelWidth;
		}

		drawRectangleColorFilled(x1, y1, x1 + labelWidth, y1 + 9, 1, c_white, c_black);
		drawText(x1 + 2, y1, label, "fnt_main", c_white, none, c_null, 0.5, 0.5);
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
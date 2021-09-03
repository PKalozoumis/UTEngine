#include "Button.h"
#include "functions.h"
#include "Game.h"
#include <iostream>
#include "Mouse.h"
#include "TextureManager.h"
#include "Debug.h"
#include "functions.h"
#include "DetectableArea.h"

Button::Button(std::string label, std::string message, int x, int y, int w, int h) : DetectableArea(label, x, y, w, h)
{
	this->message = message;
}

void Button::update(void)
{
	DetectableArea::update();

	if (boolMouseInArea && Mouse::buttonPressed(SDL_BUTTON_LMASK))
	{
		pressed = true;
	}
	else pressed = false;

	if (pressed && message != "")
	{
		Debug::addMessage(message);
	}
}

void Button::draw(void) const
{
	DetectableArea::draw();
}

bool Button::isPressed(void)
{
	return pressed;
}

void Button::setMessage(std::string message)
{
	this->message = message;
}
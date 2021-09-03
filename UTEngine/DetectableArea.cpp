#include "DetectableArea.h"
#include "Mouse.h"
#include "functions.h"
#include "Debug.h"
#include "Game.h"

DetectableArea::DetectableArea(std::string label, int x, int y, int w, int h)
{
	pos.x = x;
	pos.y = y;
	pos.w = w;
	pos.h = h;
	this->label = label;
}

void DetectableArea::update(void)
{
	if ((withinRange(Mouse::getViewX(), pos.x*2, pos.x*2 + pos.w*2))&&(withinRange(Mouse::getViewY(), pos.y*2, pos.y*2 + pos.h*2)))
	{
		boolMouseInArea = true;
	}
	else boolMouseInArea = false;
}

void DetectableArea::draw(void) const
{
	if (Debug::boolButtonHitboxes)
	{
		drawSetColor(c_lime);
		SDL_Rect tempBorder = pos;
		//tempBorder.w/=2;
		//tempBorder.h/=2;
		SDL_RenderDrawRect(Game::renderer, &tempBorder);
		drawResetColor();
	}

	int labelWidth = label.length()*4.5;

	int x1 = Mouse::getViewX()/2;
	int y1 = Mouse::getViewY()/2;

	if (boolMouseInArea && (label != ""))
	{
		if (x1 + labelWidth >= 320)
		{
			x1 -= labelWidth;
		}

		drawRectangleColorFilled(x1, y1, x1 + labelWidth, y1 + 9, 1, c_white, c_black);
		drawText(x1 + 2, y1, label, "fnt_main", c_white, none, c_null, 0.5, 0.5);
	}
}

void DetectableArea::setHeight(int height)
{
	pos.h = height;
}

void DetectableArea::setWidth(int width)
{
	pos.w = width;
}

void DetectableArea::setPos(SDL_Rect rect)
{
	pos = rect;
}

bool DetectableArea::mouseInArea(void) const
{
	return boolMouseInArea;
}
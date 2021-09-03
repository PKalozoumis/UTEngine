#pragma once
#include "SDL.h"
#include <iostream>

class DetectableArea
{
	protected:
		SDL_Rect pos;
		bool boolMouseInArea;

	private:
		std::string label;

	public:
		DetectableArea(std::string label = "", int x = 0, int y = 0, int w = 0, int h = 0);

		virtual void update(void);
		virtual void draw(void) const;

		void setPos(SDL_Rect rect);

		void setWidth(int width);
		void setHeight(int height);

		bool mouseInArea(void) const;
};


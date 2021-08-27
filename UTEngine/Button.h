#pragma once
#include "SDL.h"
#include <iostream>

class Button
{
	protected:
		SDL_Rect border;
		bool mouseOnButton = false;
		bool pressed = false;

	public:
		Button(int x=0, int y=0, int w=0, int h=0);

		virtual void update(void);
		virtual void draw(void);

		bool checkMouseOnButton(void) const;

		void setWidth(int width);
		void setHeight(int height);

		void setBorder(SDL_Rect rect);

		bool isPressed(void);
};


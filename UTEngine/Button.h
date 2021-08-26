#pragma once

#include "SDL.h"

class Button
{
	private:
		SDL_Rect border;
		bool mouseOnButton = false;

	public:
		Button(int x=0, int y=0, int w=0, int h=0);

		void update(void);
		void draw(void);

		bool checkMouseOnButton(void) const;

		void setWidth(int width);
		void setHeight(int height);

		void setBorder(SDL_Rect rect);
};


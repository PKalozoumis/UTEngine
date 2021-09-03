#pragma once
#include "SDL.h"
#include "DetectableArea.h"
#include <iostream>

class Button : public DetectableArea
{
	protected:
		bool pressed = false;

	private:
		std::string message;

	public:
		Button(std::string label = "", std::string message = "", int x=0, int y=0, int w=0, int h=0);

		void update(void);
		void draw(void) const;

		void setMessage(std::string message);

		bool isPressed(void);
};


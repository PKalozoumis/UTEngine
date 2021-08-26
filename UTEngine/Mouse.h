#pragma once

#include "Vec2.h"
#include "SDL.h"

class Mouse
{
	private:
		static Vec2<int> posInView, truePos;
		static float scale;
		static Uint32 preFrame, curFrame;
		static int deltaX, deltaY, wheelDelta;

	public:
		static void update(void);
		static int getViewX(void);
		static int getViewY(void);
		static int getTrueX(void);
		static int getTrueY(void);
		static int getDeltaX(void);
		static int getDeltaY(void);
		static int getWheelDelta(void);

		static void setWheelDelta(int wheelDelta);

		static bool button(Uint32 button);
		static bool buttonPressed(Uint32 button);
		static bool buttonReleased(Uint32 button);
};


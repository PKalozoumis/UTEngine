#include "Mouse.h"
#include "Game.h"
#include "SDL.h"

Vec2<int> Mouse::posInView, Mouse::truePos;
float Mouse::scale;
Uint32 Mouse::preFrame, Mouse::curFrame;
int Mouse::deltaX, Mouse::deltaY, Mouse::wheelDelta;

void Mouse::update(void)
{
	//Mouse position
	int windowHeight;

	SDL_GetMouseState(&truePos.x, &truePos.y);
	SDL_GetWindowSize(Game::window, NULL, &windowHeight);

	scale = (static_cast<float>(windowHeight) / 480);

	posInView.x = truePos.x/scale - 240*Game::getFullscreen()/scale;
	posInView.y = truePos.y/scale;

	//Mouse input
	preFrame = curFrame;
	curFrame = SDL_GetRelativeMouseState(&deltaX, &deltaY);
}

int Mouse::getViewX(void)
{
	return posInView.x;
}

int Mouse::getViewY(void)
{
	return posInView.y;
}

int Mouse::getTrueX(void)
{
	return truePos.x;
}

int Mouse::getTrueY(void)
{
	return truePos.y;
}

bool Mouse::button(Uint32 button)
{
	return curFrame & button;
}

bool Mouse::buttonPressed(Uint32 button)
{
	return (~preFrame) & curFrame & button;
}

bool Mouse::buttonReleased(Uint32 button)
{
	return (~curFrame) & preFrame & button;
}

int Mouse::getDeltaX(void)
{
	return deltaX;
}

int Mouse::getDeltaY(void)
{
	return deltaY;
}

int Mouse::getWheelDelta(void)
{
	return wheelDelta;
}

void Mouse::setWheelDelta(int wheelDelta)
{
	Mouse::wheelDelta = wheelDelta;
}
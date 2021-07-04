#pragma once

#include "SDL.h"

class Controller
{
	public:
		static const SDL_Scancode keyConfirm	= SDL_SCANCODE_Z;
		static const SDL_Scancode keyCancel		= SDL_SCANCODE_X;
		static const SDL_Scancode keyMeny		= SDL_SCANCODE_C;
		static const SDL_Scancode keyFullscreen	= SDL_SCANCODE_F4;
		static const SDL_Scancode keyExit		= SDL_SCANCODE_ESCAPE;
		static const SDL_Scancode keyUp			= SDL_SCANCODE_UP;
		static const SDL_Scancode keyDown		= SDL_SCANCODE_DOWN;
		static const SDL_Scancode keyLeft		= SDL_SCANCODE_LEFT;
		static const SDL_Scancode keyRight		= SDL_SCANCODE_RIGHT;
};


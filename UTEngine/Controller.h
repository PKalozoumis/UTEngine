#pragma once
#include "SDL.h"
#include <map>
#include <iostream>
#include <vector>

class Controller
{
	private:
		static const Uint8 *preFrame;
		static const Uint8 *curFrame;
		static std::map<std::string, SDL_Scancode> key;
		static int arraySize;

	public:
		static void update(void);
		static void init(void);
		static void remap(std::string function, SDL_Scancode key);

		static bool buttonPressed(std::string function);
		static bool button(std::string function);
		static bool buttonReleased(std::string function);

		static bool buttonPressed(SDL_Scancode scancode);
		static bool button(SDL_Scancode scancode);
		static bool buttonReleased(SDL_Scancode scancode);

		static SDL_Scancode randomButton(void);
		static SDL_Scancode randomButtonPressed(void);
		static SDL_Scancode randomButtonReleased(void);
};


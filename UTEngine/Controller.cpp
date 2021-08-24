#include "Controller.h"
#include "Game.h"
#include "SDL.h"
#include <iostream>
#include <map>

int Controller::arraySize;
const Uint8* Controller::preFrame;
const Uint8* Controller::curFrame;
std::map<std::string, SDL_Scancode> Controller::key;

void Controller::init(void)
{
	key.insert(std::pair<std::string, SDL_Scancode>("keyConfirm", SDL_SCANCODE_Z));
	key.insert(std::pair<std::string, SDL_Scancode>("keyCancel", SDL_SCANCODE_X));
	key.insert(std::pair<std::string, SDL_Scancode>("keyMenu", SDL_SCANCODE_C));
	key.insert(std::pair<std::string, SDL_Scancode>("keyUp", SDL_SCANCODE_UP));
	key.insert(std::pair<std::string, SDL_Scancode>("keyDown", SDL_SCANCODE_DOWN));
	key.insert(std::pair<std::string, SDL_Scancode>("keyLeft", SDL_SCANCODE_LEFT));
	key.insert(std::pair<std::string, SDL_Scancode>("keyRight", SDL_SCANCODE_RIGHT));
	key.insert(std::pair<std::string, SDL_Scancode>("keyFullscreen", SDL_SCANCODE_F4));
	key.insert(std::pair<std::string, SDL_Scancode>("keyScreenshot", SDL_SCANCODE_F2));
	key.insert(std::pair<std::string, SDL_Scancode>("keyEnd", SDL_SCANCODE_ESCAPE));

	curFrame = SDL_GetKeyboardState(&arraySize);
	preFrame = new Uint8[arraySize];
}

void Controller::update(void)
{
	memcpy((void*)preFrame, curFrame, arraySize);
}

bool Controller::buttonPressed(std::string function)
{
	return ((preFrame[key[function]] == 0) && (curFrame[key[function]] == 1));
}

bool Controller::button(std::string function)
{
	//std::cout << "(" << (int)preFrame[key[function]] << ", " << (int)curFrame[key[function]] << ")" << std::endl;
	return (curFrame[key[function]] == 1);
}

bool Controller::buttonReleased(std::string function)
{
	return ((curFrame[key[function]] == 0) && (preFrame[key[function]] == 1));
}

bool Controller::buttonPressed(SDL_Scancode scancode)
{
	return ((preFrame[scancode] == 0) && (curFrame[scancode] == 1));
}

bool Controller::button(SDL_Scancode scancode)
{
	//std::cout << "(" << (int)preFrame[key[function]] << ", " << (int)curFrame[key[function]] << ")" << std::endl;
	return (curFrame[scancode] == 1);
}

bool Controller::buttonReleased(SDL_Scancode scancode)
{
	return ((curFrame[scancode] == 0) && (preFrame[scancode] == 1));
}

void Controller::remap(std::string function, SDL_Scancode scancode)
{
	key.find(function)->second = scancode;
}

SDL_Scancode Controller::randomButton(void)
{
	for (int i = 0; i < arraySize; i++)
	{
		if (curFrame[i] == 1)
		{
			return static_cast<SDL_Scancode>(i);
		}
	}
	
	return SDL_SCANCODE_UNKNOWN;
}

SDL_Scancode Controller::randomButtonPressed(void)
{
	for (int i = 0; i < arraySize; i++)
	{
		if ((preFrame[i] == 0) && (curFrame[i] == 1))
		{
			return static_cast<SDL_Scancode>(i);
		}
	}

	return SDL_SCANCODE_UNKNOWN;
}

SDL_Scancode Controller::randomButtonReleased(void)
{
	for (int i = 0; i < arraySize; i++)
	{
		if ((preFrame[i] == 1) && (curFrame[i] == 0))
		{
			return static_cast<SDL_Scancode>(i);
		}
	}

	return SDL_SCANCODE_UNKNOWN;
}
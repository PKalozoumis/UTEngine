#pragma once

#include <iostream>
#include "Text.h"
#include <map>
#include "Button.h"

enum DebugInfo
{
	currentRoom,
	playerX,
	playerY,
	mouseX,
	mouseY,
	buttonHitboxes,
	lastPress,
	lastRelease,
	holding,
	winWidth,
	winHeight,
	mouseDeltaX,
	mouseDeltaY,
	mouseWheelDelta,

	printRoomRegistry,
	printFontRegistry,
	printTileRegistry,
	printTilesetRegistry,
	saveTheGame
};

class Debug
{
	public:
		void init(void);
		void update(void);
		void draw(void);
		static bool boolButtonHitboxes;

	private:
		std::map<DebugInfo, Text*> textMap;
		std::map<DebugInfo, Button*> buttonMap;
		bool clickedButton = false;	
};


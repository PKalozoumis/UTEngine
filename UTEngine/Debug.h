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
	amogusModeButton,

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
		static void addMessage(std::string message);

	private:
		std::map<DebugInfo, Text*> textMap;
		std::map<DebugInfo, Button*> buttonMap;
		bool clickedButton = false;
		static std::vector<std::string> messages;
		int messageStart;
		static int messageStartOffset;
		int maxNumberOfMessages = 4;
		static bool amogusMode;
};


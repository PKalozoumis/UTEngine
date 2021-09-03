#pragma once

#include <iostream>
#include "Text.h"
#include <map>
#include "SDL_mixer.h"
#include "DetectableArea.h"

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
	debugShowCameraBorders,
	debugMaxMessages,

	printRoomRegistry,
	printFontRegistry,
	printTileRegistry,
	printTilesetRegistry,
	debugPrintMusicRegistry,
	debugPrintSoundRegistry,
	saveTheGame,

	debugMessageScrollArea
};

class Debug
{
	public:
		static void init(void);
		static void update(void);
		static void draw(void);
		static bool boolButtonHitboxes;
		static void addMessage(std::string message);

	private:
		static std::map<DebugInfo, Text*> textMap;
		static std::map<DebugInfo, DetectableArea*> buttonMap;
		static bool clickedButton;
		static std::vector<std::string> messages;
		static int messageStart;
		static int messageStartOffset;
		static int maxNumberOfMessages;
		static bool amogusMode;
		static bool showCameraBorders;

		static bool debugButtonPressed(DebugInfo button);
};


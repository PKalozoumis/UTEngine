#include "Debug.h"
#include "Game.h"
#include "Text.h"
#include "Button.h"
#include "SDL.h"
#include "Controller.h"
#include "Mouse.h"
#include <iostream>
#include "functions.h"
#include "color.h"
#include "Sprite.h"
#include "SpriteButton.h"
#include <vector>
#include "SDL_mixer.h"

bool Debug::boolButtonHitboxes = false;
std::vector<std::string> Debug::messages;
int Debug::messageStartOffset = 0;
int Debug::messageStart;
int Debug::maxNumberOfMessages = 4;
bool Debug::amogusMode = false;
bool Debug::showCameraBorders = false;
std::map<DebugInfo, Text*> Debug::textMap;
std::map<DebugInfo, DetectableArea*> Debug::buttonMap;
bool Debug::clickedButton = false;

void Debug::init(void)
{
	//Current room
	textMap.insert(std::map<DebugInfo, Text*>::value_type
	(
		currentRoom,
		new Text(2, 0, "", "fnt_main", c_white, full, c_black, 0.5, 0.5, true)
	));

	//Player X
	textMap.insert(std::map<DebugInfo, Text*>::value_type
	(
		playerX,
		new Text(2, 9, "", "fnt_main", c_white, full, c_black, 0.5, 0.5, true)
	));
	
	//Player Y
	textMap.insert(std::map<DebugInfo, Text*>::value_type
	(
		playerY,
		new Text(2, 2*9, "", "fnt_main", c_white, full, c_black, 0.5, 0.5, true)
	));
	
	//Mouse X
	textMap.insert(std::map<DebugInfo, Text*>::value_type
	(
		mouseX,
		new Text(2,  3*9, "", "fnt_main", c_white, full, c_black, 0.5, 0.5, true)
	));
	
	//Mouse Y
	textMap.insert(std::map<DebugInfo, Text*>::value_type
	(
		mouseY,
		new Text(2, 4*9, "", "fnt_main", c_white, full, c_black, 0.5, 0.5, true)
	));
	
	//Button hitboxes
	textMap.insert(std::map<DebugInfo, Text*>::value_type
	(
		buttonHitboxes,
		new Text(2, 5*9, "", "fnt_main", c_white, full, c_black, 0.5, 0.5, true)
	));

	buttonMap.insert(std::map<DebugInfo, DetectableArea*>::value_type(buttonHitboxes, new Button("Toggle Button Hitboxes", "Toggled button hitboxes", 295, 5, 40,40)));
	
	//Last Pressed
	textMap.insert(std::map<DebugInfo, Text*>::value_type
	(
		lastPress,
		new Text(2, 6*9, "", "fnt_main", c_white, full, c_black, 0.5, 0.5, true)
	));
	
	//Last Released
	textMap.insert(std::map<DebugInfo, Text*>::value_type
	(
		lastRelease,
		new Text(2, 7*9, "", "fnt_main", c_white, full, c_black, 0.5, 0.5, true)
	));
	
	//Holding
	textMap.insert(std::map<DebugInfo, Text*>::value_type
	(
		holding,
		new Text(2, 8*9, "", "fnt_main", c_white, full, c_black, 0.5, 0.5, true)
	));
	
	//Window Width
	textMap.insert(std::map<DebugInfo, Text*>::value_type
	(
		winWidth,
		new Text(2, 9*9, "", "fnt_main", c_white, full, c_black, 0.5, 0.5, true)
	));
	
	//Window Height
	textMap.insert(std::map<DebugInfo, Text*>::value_type
	(
		winHeight,
		new Text(2, 10*9, "", "fnt_main", c_white, full, c_black, 0.5, 0.5, true)
	));
	
	//Mouse Delta X
	textMap.insert(std::map<DebugInfo, Text*>::value_type
	(
		mouseDeltaX,
		new Text(2, 11*9, "", "fnt_main", c_white, full, c_black, 0.5, 0.5, true)
	));
	
	//Mouse Delta Y
	textMap.insert(std::map<DebugInfo, Text*>::value_type
	(
		mouseDeltaY,
		new Text(2, 12*9, "", "fnt_main", c_white, full, c_black, 0.5, 0.5, true)
	));
	
	//Mouse Wheel Delta
	textMap.insert(std::map<DebugInfo, Text*>::value_type
	(
		mouseWheelDelta,
		new Text(2, 13*9, "", "fnt_main", c_white, full, c_black, 0.5, 0.5, true)
	));

	//Amogus mode
	textMap.insert(std::map<DebugInfo, Text*>::value_type
	(
		amogusModeButton,
		new Text(2, 14*9, "", "fnt_main", c_white, full, c_black, 0.5, 0.5, true)
	));

	buttonMap.insert(std::map<DebugInfo, DetectableArea*>::value_type(amogusModeButton, new Button("Toggle Amogus Mode", "Toggled Amogus Mode")));

	//Show camera borders
	textMap.insert(std::map<DebugInfo, Text*>::value_type
	(
		debugShowCameraBorders,
		new Text(2, 15*9, "", "fnt_main", c_white, full, c_black, 0.5, 0.5, true)
	));

	buttonMap.insert(std::map<DebugInfo, DetectableArea*>::value_type(debugShowCameraBorders, new Button("Toggle Camera Borders", "Toggled Camera Borders")));

	//Max messages
	textMap.insert(std::map<DebugInfo, Text*>::value_type
	(
		debugMaxMessages,
		new Text(2, 16*9, "", "fnt_main", c_white, full, c_black, 0.5, 0.5, true)
	));

	buttonMap.insert(std::map<DebugInfo, DetectableArea*>::value_type(debugMaxMessages, new Button("Set Max Messages", "")));

	//Room registry
	buttonMap.insert(std::map<DebugInfo, DetectableArea*>::value_type(printRoomRegistry, new SpriteButton("assets/sprites/debug/sprDebugPrintRooms.png", "Print Room Registry", "Printed room registry", 295, 5)));

	//Font registry
	buttonMap.insert(std::map<DebugInfo, DetectableArea*>::value_type(printFontRegistry, new SpriteButton("assets/sprites/debug/sprDebugPrintFonts.png", "Print Font Registry", "Printed font registry", 295, 30)));

	//Tile registry
	buttonMap.insert(std::map<DebugInfo, DetectableArea*>::value_type(printTileRegistry, new SpriteButton("assets/sprites/debug/sprDebugPrintTiles.png", "Print Tile Registry", "Printed tile registry", 295, 55)));

	//Tileset registry
	buttonMap.insert(std::map<DebugInfo, DetectableArea*>::value_type(printTilesetRegistry, new SpriteButton("assets/sprites/debug/sprDebugPrintTilesets.png", "Print Tileset Registry", "Printed tileset registry", 295, 80)));

	//Music registry
	buttonMap.insert(std::map<DebugInfo, DetectableArea*>::value_type(debugPrintMusicRegistry, new SpriteButton("assets/sprites/debug/sprDebugPrintMusic.png", "Print Music Registry", "Printed music registry", 295, 105)));

	//Sound registry
	buttonMap.insert(std::map<DebugInfo, DetectableArea*>::value_type(debugPrintSoundRegistry, new SpriteButton("assets/sprites/debug/sprDebugPrintSounds.png", "Print Sound Registry", "Printed sound registry", 295, 130)));

	//Save the game
	buttonMap.insert(std::map<DebugInfo, DetectableArea*>::value_type(saveTheGame, new SpriteButton("assets/sprites/debug/sprDebugSave.png", "Save", "Game saved", 295, 155)));

	//Message scroll area
	buttonMap.insert(std::map<DebugInfo, DetectableArea*>::value_type(debugMessageScrollArea, new DetectableArea("", 18, 170, 110, 40)));
}

void Debug::update(void)
{
	static SDL_Scancode lastPressed = Controller::randomButtonPressed();
	static SDL_Scancode lastReleased = Controller::randomButtonReleased();

	SDL_Scancode newPressed = Controller::randomButtonPressed();
	SDL_Scancode newReleased = Controller::randomButtonReleased();

	if ((newPressed != lastPressed)&&(newPressed != 0))
		lastPressed = newPressed;

	if ((newReleased != lastReleased)&&(newReleased != 0))
		lastReleased = newReleased;

	int windowWidth, windowHeight;

	SDL_GetWindowSize(Game::window, &windowWidth, &windowHeight);

	textMap[currentRoom]->refreshText("Current Room: " + Game::getRoomFilename());
	textMap[playerX]->refreshText("x: " + std::to_string(Game::playerX()));
	textMap[playerY]->refreshText("y: " + std::to_string(Game::playerY()));
	textMap[mouseX]->refreshText("Mouse x: " + std::to_string(Mouse::getViewX()));
	textMap[mouseY]->refreshText("Mouse y: " + std::to_string(Mouse::getViewY()));
	textMap[buttonHitboxes]->refreshText("Button hitboxes: " + std::to_string(boolButtonHitboxes));
	textMap[holding]->refreshText("Holding: " + std::string(SDL_GetScancodeName(Controller::randomButton())));
	textMap[lastRelease]->refreshText("Last released: " + std::string(SDL_GetScancodeName(lastReleased)));
	textMap[lastPress]->refreshText("Last pressed: " + std::string(SDL_GetScancodeName(lastPressed)));
	textMap[winWidth]->refreshText("Window width: " + std::to_string(windowWidth));
	textMap[winHeight]->refreshText("Window height: " + std::to_string(windowHeight));
	textMap[mouseDeltaX]->refreshText("Mouse Delta X: " + std::to_string(Mouse::getDeltaX()));
	textMap[mouseDeltaY]->refreshText("Mouse Delta Y: " + std::to_string(Mouse::getDeltaY()));
	textMap[mouseWheelDelta]->refreshText("Mouse Wheel Delta: " + std::to_string(Mouse::getWheelDelta()));
	textMap[amogusModeButton]->refreshText("Amogus Mode: " + std::to_string(amogusMode));
	textMap[debugShowCameraBorders]->refreshText("Show Camera Borders: " + std::to_string(showCameraBorders));
	textMap[debugMaxMessages]->refreshText("Max Num of Messages On View: " + std::to_string(maxNumberOfMessages));

	static_cast<Button*>(buttonMap[amogusModeButton])->setMessage("Set Amogus Mode to " + std::to_string(!amogusMode));
	static_cast<Button*>(buttonMap[buttonHitboxes])->setMessage("Set Button Hitboxes to " + std::to_string(!boolButtonHitboxes));
	static_cast<Button*>(buttonMap[debugShowCameraBorders])->setMessage("Set Camera Borders to " + std::to_string(!showCameraBorders));

	for (auto& pair : buttonMap)
	{
		if (textMap.count(pair.first) > 0)
		{
			SDL_Rect tempPos = textMap[pair.first]->getPos();
			tempPos.w /= 2;
			tempPos.h /= 2;
			pair.second->setPos(tempPos);
		}

		pair.second->update();
	}

	//Button actions

		if (debugButtonPressed(printRoomRegistry))
			Game::roomRegistry.printOrdered();

		if (debugButtonPressed(buttonHitboxes))
			boolButtonHitboxes = !boolButtonHitboxes;

		//if (buttonMap[printFontRegistry]->isPressed())
			//Game::fontRegistry.printOrdered();

		if (debugButtonPressed(printTileRegistry))
			Game::tileRegistry.printOrdered();

		if (debugButtonPressed(printTilesetRegistry))
			Game::tilesetRegistry.printOrdered();

		if (debugButtonPressed(debugPrintMusicRegistry))
			Game::musicRegistry.printOrdered();

		if (debugButtonPressed(saveTheGame))
			Game::save();

		if (debugButtonPressed(amogusModeButton))
			amogusMode = !amogusMode;

		if (debugButtonPressed(debugShowCameraBorders))
			showCameraBorders = !showCameraBorders;

		if (debugButtonPressed(debugPrintSoundRegistry))
			Game::soundRegistry.printOrdered();

		if (buttonMap[debugMessageScrollArea]->mouseInArea())
		{
			if (Mouse::getWheelDelta() < 0)
			{
				if (messageStartOffset - 1 >=0)
				{
					messageStartOffset--;
				}
			}
			else if (Mouse::getWheelDelta() > 0)
			{
				if (messageStartOffset + 1 <= messageStart)
				{
					messageStartOffset++;
				}
			}
		}

	messageStart = (messages.size() >= maxNumberOfMessages)?(messages.size()-maxNumberOfMessages):(0);
}

void Debug::draw(void)
{
	if (showCameraBorders)
	{
		drawRectangleColor(-Game::camera.x, - Game::camera.y, Game::getRoomWidth() - Game::camera.x, Game::getRoomHeight() - Game::camera.y, 1, c_lime);
		drawRectangleColor(-Game::camera.x, 120 - Game::camera.y, Game::getRoomWidth(), Game::getRoomHeight() - 120 - Game::camera.y, 1, c_blue);
		drawRectangleColor(160 - Game::camera.x, - Game::camera.y, Game::getRoomWidth() - 160 - Game::camera.x, Game::getRoomHeight(), 1, c_red);
	}

	for (auto& pair : textMap)
	{
		pair.second->draw();
	}

	for (auto& pair : buttonMap)
	{
		pair.second->draw();
	}

	//Input box
	drawRectangleColorFilled(10, 210, 310, 235, 3, c_gray, c_black);

	//Messages
	int end = messages.size() - messageStartOffset;

	for (int i = messageStart - messageStartOffset; i < end; i++)
	{
		drawText(20, 209 - 9*(messages.size() - messageStartOffset - i), /*std::to_string(i) + " " + */"< System > " + messages[i], "fnt_main", c_white, full, c_black, 0.5, 0.5);
	}

	//Scrollbar

	if (messages.size() > 0)
	{
		drawRectangleColorFilled(10, 172, 17, 208, 1, c_white, c_black);
		int add = (messages.size() > 3)?(34/(messages.size()-3)):(34);
		drawRectangleColorFilled(11, 173, 16, 173 + add, 1, c_black, c_gray);
	}
}

void Debug::addMessage(std::string message)
{
	messages.push_back(message);
	messageStartOffset = 0;
}

bool Debug::debugButtonPressed(DebugInfo button)
{
	if (buttonMap.find(button) != buttonMap.end())
		return static_cast<Button*>(buttonMap[button])->isPressed();
}
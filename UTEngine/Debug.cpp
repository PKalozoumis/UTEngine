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

bool Debug::boolButtonHitboxes = false;
std::vector<std::string> Debug::messages;
int Debug::messageStartOffset = 0;
bool Debug::amogusMode = false;

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

	buttonMap.insert(std::map<DebugInfo, Button*>::value_type(buttonHitboxes, new Button("Toggle Button Hitboxes", "Toggled button hitboxes", 295, 5, 40,40)));
	
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

	buttonMap.insert(std::map<DebugInfo, Button*>::value_type(amogusModeButton, new Button("Toggle Amogus Mode", "Toggled Amogus Mode")));

	//Room registry
	buttonMap.insert(std::map<DebugInfo, Button*>::value_type(printRoomRegistry, new SpriteButton("assets/sprites/debug/sprDebugPrintRooms.png", "Print Room Registry", "Printed room registry", 295, 5)));

	//Font registry
	buttonMap.insert(std::map<DebugInfo, Button*>::value_type(printFontRegistry, new SpriteButton("assets/sprites/debug/sprDebugPrintFonts.png", "Print Font Registry", "Printed font registry", 295, 30)));

	//Tile registry
	buttonMap.insert(std::map<DebugInfo, Button*>::value_type(printTileRegistry, new SpriteButton("assets/sprites/debug/sprDebugPrintTiles.png", "Print Tile Registry", "Printed tile registry", 295, 55)));

	//Tileset registry
	buttonMap.insert(std::map<DebugInfo, Button*>::value_type(printTilesetRegistry, new SpriteButton("assets/sprites/debug/sprDebugPrintTilesets.png", "Print Tileset Registry", "Printed tileset registry", 295, 80)));

	//Save the game
	buttonMap.insert(std::map<DebugInfo, Button*>::value_type(saveTheGame, new SpriteButton("assets/sprites/debug/sprDebugSave.png", "Save", "Game saved", 295, 105)));
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

	for (auto& pair : buttonMap)
	{
		if (textMap.count(pair.first) > 0)
		{
			pair.second->setBorder(textMap[pair.first]->getPos());
		}

		pair.second->update();
	}

	//Button actions

		if (buttonMap[printRoomRegistry]->isPressed())
			Game::roomRegistry.printOrdered();

		if (buttonMap[buttonHitboxes]->isPressed())
			boolButtonHitboxes = !boolButtonHitboxes;

		//if (buttonMap[printFontRegistry]->isPressed())
			//Game::fontRegistry.printOrdered();

		if (buttonMap[printTileRegistry]->isPressed())
			Game::tileRegistry.printOrdered();

		if (buttonMap[printTilesetRegistry]->isPressed())
			Game::tilesetRegistry.printOrdered();

		if (buttonMap[saveTheGame]->isPressed())
			Game::save();

		if (buttonMap[amogusModeButton]->isPressed())
			amogusMode = !amogusMode;

	messageStart = (messages.size() >= maxNumberOfMessages)?(messages.size()-maxNumberOfMessages):(0);

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

void Debug::draw(void)
{
	for (auto& pair : textMap)
	{
		pair.second->draw();
	}

	for (auto& pair : buttonMap)
	{
		pair.second->draw();
	}

	drawRectangleColorFilled(10, 210, 310, 235, 3, c_gray, c_black);

	int end = messages.size() - messageStartOffset;

	for (int i = messageStart - messageStartOffset; i < end; i++)
	{
		drawText(10, 209 - 9*(messages.size() - messageStartOffset - i), "< System > " + messages[i], "fnt_main", c_white, full, c_black, 0.5, 0.5);
	}
}

void Debug::addMessage(std::string message)
{
	messages.push_back(message);
	messageStartOffset = 0;
}
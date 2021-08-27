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

bool Debug::boolButtonHitboxes = false;

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

	buttonMap.insert(std::map<DebugInfo, Button*>::value_type(buttonHitboxes, new Button(295,5, 40,40)));
	
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

	//Room registry
	buttonMap.insert(std::map<DebugInfo, Button*>::value_type(printRoomRegistry, new SpriteButton("assets/sprites/debug/sprDebugPrintRooms.png", 295, 5)));

	//Font registry
	buttonMap.insert(std::map<DebugInfo, Button*>::value_type(printFontRegistry, new SpriteButton("assets/sprites/debug/sprDebugPrintFonts.png", 295, 30)));

	//Tile registry
	buttonMap.insert(std::map<DebugInfo, Button*>::value_type(printTileRegistry, new SpriteButton("assets/sprites/debug/sprDebugPrintTiles.png", 295, 55)));

	//Tileset registry
	buttonMap.insert(std::map<DebugInfo, Button*>::value_type(printTilesetRegistry, new SpriteButton("assets/sprites/debug/sprDebugPrintTilesets.png", 295, 80)));

	//Save the game
	buttonMap.insert(std::map<DebugInfo, Button*>::value_type(saveTheGame, new SpriteButton("assets/sprites/debug/sprDebugSave.png", 295, 105)));
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

	for (auto& pair : buttonMap)
	{
		if (textMap.count(pair.first) > 0)
		{
			pair.second->setBorder(textMap[pair.first]->getPos());
		}

		pair.second->update();
	}

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

	if (buttonMap[printRoomRegistry]->checkMouseOnButton())
	{
		drawRectangleColorFilled(Mouse::getViewX()/2 - 67, Mouse::getViewY()/2, Mouse::getViewX()/2, Mouse::getViewY()/2 + 9, 1, c_white, c_black);
		drawText(Mouse::getViewX()/2 + 2 - 67, Mouse::getViewY()/2, "Print Room Registry", "fnt_main", c_white, none, c_null, 0.5, 0.5);
	}
}
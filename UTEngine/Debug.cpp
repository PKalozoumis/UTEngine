#include "Debug.h"
#include "Game.h"
#include "Text.h"
#include "Button.h"
#include "SDL.h"
#include "Controller.h"
#include "Mouse.h"

Button butt;

void Debug::init(void)
{
	textMap.insert(std::map<std::string, Text*>::value_type
	(
		"txtCurrentRoom",
		new Text(2, 0, "Current Room: ", "fnt_main", c_white, full, c_black, 0.5, 0.5, true)
	));

	textMap.insert(std::map<std::string, Text*>::value_type
	(
		"txtPlayerX",
		new Text(2, 9, "x: ", "fnt_main", c_white, full, c_black, 0.5, 0.5, true)
	));

	textMap.insert(std::map<std::string, Text*>::value_type
	(
		"txtPlayerY",
		new Text(2, 2*9, "y: ", "fnt_main", c_white, full, c_black, 0.5, 0.5, true)
	));

	textMap.insert(std::map<std::string, Text*>::value_type
	(
		"txtMouseX",
		new Text(2,  3*9, "Mouse x: ", "fnt_main", c_white, full, c_black, 0.5, 0.5, true)
	));

	textMap.insert(std::map<std::string, Text*>::value_type
	(
		"txtMouseY",
		new Text(2, 4*9, "Mouse y: ", "fnt_main", c_white, full, c_black, 0.5, 0.5, true)
	));

	textMap.insert(std::map<std::string, Text*>::value_type
	(
		"txtMouseOnButton",
		new Text(2, 5*9, "Mouse on button: ", "fnt_main", c_white, full, c_black, 0.5, 0.5, true)
	));

	textMap.insert(std::map<std::string, Text*>::value_type
	(
		"txtLastPressed",
		new Text(2, 6*9, "Last pressed: ", "fnt_main", c_white, full, c_black, 0.5, 0.5, true)
	));

	textMap.insert(std::map<std::string, Text*>::value_type
	(
		"txtLastReleased",
		new Text(2, 7*9, "Last released: ", "fnt_main", c_white, full, c_black, 0.5, 0.5, true)
	));

	textMap.insert(std::map<std::string, Text*>::value_type
	(
		"txtHolding",
		new Text(2, 8*9, "Holding: ", "fnt_main", c_white, full, c_black, 0.5, 0.5, true)
	));

	textMap.insert(std::map<std::string, Text*>::value_type
	(
		"txtWindowWidth",
		new Text(2, 9*9, "Window width: ", "fnt_main", c_white, full, c_black, 0.5, 0.5, true)
	));

	textMap.insert(std::map<std::string, Text*>::value_type
	(
		"txtWindowHeight",
		new Text(2, 10*9, "Window height: ", "fnt_main", c_white, full, c_black, 0.5, 0.5, true)
	));

	textMap.insert(std::map<std::string, Text*>::value_type
	(
		"txtMouseDeltaX",
		new Text(2, 11*9, "Mouse Delta x: ", "fnt_main", c_white, full, c_black, 0.5, 0.5, true)
	));

	textMap.insert(std::map<std::string, Text*>::value_type
	(
		"txtMouseDeltaY",
		new Text(2, 12*9, "Mouse Delta y: ", "fnt_main", c_white, full, c_black, 0.5, 0.5, true)
	));

	textMap.insert(std::map<std::string, Text*>::value_type
	(
		"txtMouseWheelDelta",
		new Text(2, 13*9, "Mouse Wheel Delta: ", "fnt_main", c_white, full, c_black, 0.5, 0.5, true)
	));
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

	textMap["txtCurrentRoom"]->refreshText("Current Room: " + Game::getRoomFilename());
	textMap["txtPlayerX"]->refreshText("x: " + std::to_string(Game::playerX()));
	textMap["txtPlayerY"]->refreshText("y: " + std::to_string(Game::playerY()));
	textMap["txtMouseX"]->refreshText("Mouse x: " + std::to_string(Mouse::getViewX()));
	textMap["txtMouseY"]->refreshText("Mouse y: " + std::to_string(Mouse::getViewY()));
	textMap["txtMouseOnButton"]->refreshText("Mouse on button: " + std::to_string(butt.checkMouseOnButton()));
	textMap["txtHolding"]->refreshText("Holding: " + std::string(SDL_GetScancodeName(Controller::randomButton())));
	textMap["txtLastReleased"]->refreshText("Last released: " + std::string(SDL_GetScancodeName(lastReleased)));
	textMap["txtLastPressed"]->refreshText("Last pressed: " + std::string(SDL_GetScancodeName(lastPressed)));
	textMap["txtWindowWidth"]->refreshText("Window width: " + std::to_string(windowWidth));
	textMap["txtWindowHeight"]->refreshText("Window height: " + std::to_string(windowHeight));
	textMap["txtMouseDeltaX"]->refreshText("Mouse Delta X: " + std::to_string(Mouse::getDeltaX()));
	textMap["txtMouseDeltaY"]->refreshText("Mouse Delta Y: " + std::to_string(Mouse::getDeltaY()));
	textMap["txtMouseWheelDelta"]->refreshText("Mouse Wheel Delta: " + std::to_string(Mouse::getWheelDelta()));

	butt.setBorder(textMap["txtCurrentRoom"]->getPos());

	butt.update();

	if (Mouse::button(SDL_BUTTON_LMASK))
		std::cout << "Left mouse button held" << std::endl;

	if (Mouse::buttonPressed(SDL_BUTTON_RMASK))
		std::cout << "Right mouse button pressed" << std::endl;

	if (Mouse::buttonReleased(SDL_BUTTON_MMASK))
		std::cout << "Middle mouse button released" << std::endl;
}

void Debug::draw(void)
{
	for (auto& pair : textMap)
	{
		pair.second->draw();
	}

	butt.draw();
}
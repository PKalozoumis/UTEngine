#include "Debug.h"
#include "Game.h"
#include "Text.h"

void Debug::init(void)
{
	textMap.insert(std::map<std::string, Text*>::value_type
	(
		"txtCurrentRoom",
		new Text(2, 0 , "Current Room: ", "fnt_main", c_white, full, c_black, 0.5, 0.5, true)
	));

	textMap.insert(std::map<std::string, Text*>::value_type
	(
		"txtPlayerX",
		new Text(2, 9 , "x: ", "fnt_main", c_white, full, c_black, 0.5, 0.5, true)
	));

	textMap.insert(std::map<std::string, Text*>::value_type
	(
		"txtPlayerY",
		new Text(2, 18 , "y: ", "fnt_main", c_white, full, c_black, 0.5, 0.5, true)
	));
}

void Debug::update(void)
{
	textMap["txtCurrentRoom"]->refreshText("Current Room: " + Game::getRoomFilename());
	textMap["txtPlayerX"]->refreshText("x: " + std::to_string(Game::playerX()));
	textMap["txtPlayerY"]->refreshText("y: " + std::to_string(Game::playerY()));
}

void Debug::draw(void)
{
	for (auto& pair : textMap)
	{
		pair.second->draw();
	}
}
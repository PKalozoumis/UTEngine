#include "Tileset.h"
#include <vector>
#include "Tile.h"
#include "json.hpp"
#include "functions.h"
#include "Game.h"

void Tileset::printTilesetInfo(void) const
{
	std::cout<<name<<std::endl;
	for(Tile* tile : tiles) tile->printTileInfo();
}

Tileset::Tileset(const std::string directory)
{
	nlohmann::json j = jsonLoad(directory);
	name = j["name"];
	margin = j["margin"];
	spacing = j["spacing"];
	tilecount = j["tilecount"];
	tileheight = j["tileheight"];
	tilewidth = j["tilewidth"];
	
	//Tile Registration
	for(int i = 0; i < j["tilecount"]; i++)
	{
		nlohmann::json j1 = j["tiles"][i];		
		std::string tilename = jsonToString(j1["image"]);

		if (!Game::tileRegistry.exists(tilename))
		{
			Tile* t = new Tile(j1);
			Game::tileRegistry.registration(t->getImage(), t);
		}

		tiles.push_back(Game::tileRegistry[tilename]);
	}
}

Tile* Tileset::getTile(const int index) const
{
	return tiles[index];
}

void Tileset::shiftTileId(const int shift)
{
	for(int i = 0; i < tilecount; i++)
	{
		tiles[i]->shiftTileId(shift);
	}
}

int Tileset::getTileCount(void) const
{
	return tilecount;
}

std::string Tileset::getName(void) const
{
	return name;
}

std::ostream& operator<<(std::ostream& out, Tileset& tileset)
{
	out << tileset.name;
	return out;
}
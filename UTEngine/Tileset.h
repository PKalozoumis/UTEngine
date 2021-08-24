#pragma once

#include <vector>
#include "Tile.h"
#include "json.hpp"
#include <iostream>

//I don't know why this is required
class Tile;

class Tileset
{
	private:
		std::string name;
		int margin, spacing, tilecount, tileheight, tilewidth;
		std::vector<Tile*> tiles;

	public:
		Tileset(const std::string); //Accepts the path to the tileset json file
		Tile* getTile(const int) const;
		void printTilesetInfo(void) const;
		int getTileCount(void) const;
		void shiftTileId(const int);
		std::string getName(void) const;

		friend std::ostream& operator<<(std::ostream& out, Tileset& tileset);
};


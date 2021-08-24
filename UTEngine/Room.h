#pragma once

#include <vector>
#include "Layer.h"
#include "Tile.h"
#include "Tileset.h"
#include <iostream>

//I don't know why these are required 
class Tile;
class Tileset;

class Room
{
	private:
		int layerCount, tilesetCount, tileWidth, tileHeight, width, height, id;
		std::string name;
		std::string filename;
		std::vector<int> firstgid;
		std::vector<Layer> layers;
		std::vector<std::string> tilesetKeys;

	public:
		Room(int id);
		const Tile* getTile(const int) const;
		void printLayerInfo(const int) const;
		void printData(const int) const;
		void printTilesetInfo(const int) const;
		void printRoomInfo(void) const;
		void printTilesetKeys(void) const;
		void drawRoom(void) const;
		int getWidth(void) const;
		int getHeight(void) const;
		std::string getName(void) const;
		std::string getFilename(void) const;
		void setName(std::string name);
		friend std::ostream& operator<<(std::ostream& out, const Room& room);
		int getId(void) const;
};
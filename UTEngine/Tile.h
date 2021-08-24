#pragma once

#include <iostream>
#include "json.hpp"
#include "Game.h"

class Tile
{
	private:
		int id;
		std::string image;
		int imageheight;
		int imagewidth;
		SDL_Texture* sprite;

	public:
		int getId(void) const;
		std::string getImage(void) const;
		int getHeight(void) const;
		int getWidth(void) const;
		void printTileInfo(void) const;
		void shiftTileId(const int);
		SDL_Texture* getSprite(void) const;

		Tile(const nlohmann::json);
		Tile(const std::string directory, const int id);
		//~Tile(void);

		friend std::ostream& operator<<(std::ostream& out, Tile& tile);
};

#include "Tile.h"
#include "functions.h"
#include "Game.h"
#include <iostream>
#include "TextureManager.h"

int Tile::getId(void) const
{
	return id;
}

void Tile::shiftTileId(const int shift)
{
	id += shift;
}

std::string Tile::getImage(void) const
{
	return image;
}

int Tile::getHeight(void) const
{
	return imageheight;
}

int Tile::getWidth(void) const
{
	return imagewidth;
}

void Tile::printTileInfo(void) const
{
	std::cout <<
		"_____________TILE INFO_____________\n"
		"ID: " << id <<
		"\nFilename: " << image <<
		"\nWidth: " << imagewidth <<
		"\nHeight: " << imageheight <<
		"\n___________________________________" <<
	std::endl;
}

Tile::Tile(const nlohmann::json j)
{
	id = j["id"];
	image = j["image"];
	imageheight = j["imageheight"];
	imagewidth = j["imagewidth"];

	sprite = TextureManager::loadTexture("assets/sprites/tiles/" + image);
}

Tile::Tile(const std::string directory, const int id)
{
	nlohmann::json j = jsonLoad(directory)["tiles"][id];

	this->id = j["id"];
	image = j["image"];
	imageheight = j["imageheight"];
	imagewidth = j["imagewidth"];

	sprite = TextureManager::loadTexture("assets/sprites/tiles/" + image);
}

/*Tile::~Tile(void)
{
	SDL_DestroyTexture(sprite);
}*/

SDL_Texture* Tile::getSprite(void) const
{
	return sprite;
}

std::ostream& operator<<(std::ostream& out, Tile& tile)
{
	out << tile.image;
	return out;
}

#include "Room.h"
#include "iostream"
#include "json.hpp"
#include "functions.h"
#include "string"
#include "TextureManager.h"
#include "Tile.h"
#include <string>
#include "Game.h"

Room::Room(int id)
{
    nlohmann::json rm = jsonLoad("assets/data/rooms.json")["rooms"][id];

    this->id = id;
    name = rm["name"];
    filename = rm["filename"];

    std::string directory = "assets/sprites/tiles/" + filename;
	nlohmann::json j = jsonLoad(directory);

    width = j["width"];
    height = j["height"];
    tileWidth = j["tilewidth"];
    tileHeight = j["tileheight"];

    //Tileset initialization

    nlohmann::json tArray = j["tilesets"];

    tilesetCount = tArray.size();

    for(int i = 0; i < tilesetCount; i++)
    {
        firstgid.push_back(tArray[i]["firstgid"]);
        std::string fname = tArray[i]["source"];

        auto pos = fname.find_last_of(".");
        fname.replace(pos + 1, std::string::npos,"json");
        
        if (!Game::tilesetRegistry.exists(fname))
        {
            Game::tilesetRegistry.registration(fname, new Tileset("assets/sprites/tiles/" + fname));
            std::cout<<"Added " + fname + " to the tileset registry"<<std::endl;
        }

        tilesetKeys.push_back(fname);
    }

    //Layer initialization

    nlohmann::json layerArray = j["layers"];

    layerCount = layerArray.size();

    for(int i = 0; i < layerCount; i++)
    {
        layers.push_back(Layer(layerArray[i]));
    }
}

void Room::printLayerInfo(const int layer) const
{
    layers[layer].printLayerInfo();
}

void Room::printData(const int layer) const
{
    layers[layer].printData();
}

void Room::printTilesetInfo(const int tileset) const
{
    Game::tilesetRegistry[tilesetKeys[tileset]]->printTilesetInfo();
}

void Room::printTilesetKeys(void) const
{
    std::cout << "==================== TILESET KEYS ====================" << std::endl;

    for (std::string key : tilesetKeys)
        std::cout << key << std::endl;
}

const Tile* Room::getTile(const int tileNum) const
{
    int subtr;
    int tilesetNum = -1;

    for(int i = 0; i < tilesetCount; i++)
    {
        if(tileNum >= firstgid[tilesetCount - 1 - i])
        {
            if (withinRange(tileNum, firstgid[tilesetCount - 1 - i], firstgid[tilesetCount - 1 - i] + Game::tilesetRegistry[tilesetKeys[tilesetCount - 1 - i]]->getTileCount() - 1))
            {
                tilesetNum = tilesetCount - 1 - i;
                subtr = firstgid[tilesetCount - 1 - i];
                break;
            }
        }
    }

    if (tilesetNum == -1)
    {
        return Game::tileRegistry["tile_air.png"];
    }
    else return Game::tilesetRegistry[tilesetKeys[tilesetNum]]->getTile(tileNum - subtr);
}

void Room::drawRoom(void) const
{
    SDL_Rect src, dest;

    for(int i = 0; i < layerCount; i++)
    {
        if (!layers[i].getVisible())
        {
            continue;
        }

        for(int j = 0; j < layers[i].getHeight(); j++)
        {
            for(int k = 0; k < layers[i].getWidth(); k++)
            {
               const Tile* t = getTile(layers[i].getTileAt(j, k));

               src.x = 0;
               src.y = 0;
               src.w = t->getWidth();
               src.h = t->getHeight();

               dest.x = k*tileWidth - Game::camera.x; //Removing camera.x gives absolute position
               dest.y = j*tileHeight - Game::camera.y; //Removing camera.y gives absolute position
               dest.w = src.w;
               dest.h = src.h;

               if ((dest.x + dest.w >= 0)&&(dest.y + dest.h >= 0))
                TextureManager::draw(t->getSprite(), src, dest);
            }
        }
    }
}

int Room::getWidth(void) const
{
    return width*tileWidth;
}

int Room::getHeight(void) const
{
    return height*tileHeight;
}

std::string Room::getName(void) const
{
    return name;
}

std::string Room::getFilename(void) const
{
    return filename;
}

std::ostream& operator<<(std::ostream& out, const Room& room)
{
    out << room.filename;
    return out;
}

void Room::setName(std::string name)
{
    this->name = name;
}

void Room::printRoomInfo(void) const
{
    std::cout <<
	"=============== ROOM INFO ===============\n"
    "Name: " << name <<
	"\nFilename: " << filename <<
    "\nID: " << id <<
	"\n==============================" <<
    std::endl;
}

int Room::getId(void) const
{
    return id;
}
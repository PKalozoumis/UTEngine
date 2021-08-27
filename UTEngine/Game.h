#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include "ECS.h"
#include "Registry.h"
#include "SDL_ttf.h"
#include "Room.h"
#include "Tile.h"
#include "Tileset.h"
#include <map>
#include "Menu.h"
#include <cstdlib>
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include <vector>
#include "Text.h"
#include "Debug.h"

class Room;

class Game
{
	public:
		//Registries
		static Registry<std::string, TTF_Font*> fontRegistry;
		static Registry<std::string, Tile*> tileRegistry;
		static Registry<std::string, Tileset*> tilesetRegistry;
		static Registry<std::string, Room*> roomRegistry;

		static SDL_Window* window;
		static SDL_Renderer* renderer;
		static SDL_Event event;
		static Manager manager;
		static Entity& player;
		static SDL_Rect camera;
		static Room* currentRoom;
		static Menu menu;

		Game(void);
		~Game(void);

		void init(std::string title, int xpos, int ypos, int width, int height, bool fullscreen, std::string room = "room_testmap.json");
		void handleEvents(void);
		void update(void);
		void endFrame(void);
		void render(void);
		void clean(void);
		
		bool running(void);

		void loadRooms(void);
		void loadFonts(void);

		void loadJoysticks(void);

		static void roomGoto(int roomID);
		static void roomGotoNext(void);
		static void roomGotoPrevious(void);

		static bool getFullscreen(void);
		static bool getToggledFullscreen(void);

		static bool getPlayerPosInView(void);

		static int getXbor(void);
		static int getYbor(void);

		static int playerX(void);
		static int playerY(void);

		static std::string getRoomFilename(void);
		static std::string getRoomName(void);

		static void save(void);

	private:
		std::vector<Text*> textVector;

		int screenshotWidth, screenshotHeight;
		static std::string mainPath;
		static std::string savePath;
		static std::string screenshotPath;
		unsigned int gameTime = 0;
		bool isRunning;
		std::vector<SDL_Joystick*> joysticks;
		static bool toggledFullscreen;
		static bool playerPosInView; //0 for top half, 1 for bottom half
		static int xbor, ybor;
		static TransformComponent* playerTransform;
		static SpriteComponent* playerSprite;

		Debug debug;
		bool debugMode = false;
};


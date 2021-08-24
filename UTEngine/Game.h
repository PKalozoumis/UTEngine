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
		static int xbor, ybor;

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

	private:
		int screenshotWidth, screenshotHeight;
		std::string mainPath;
		std::string savePath;
		std::string screenshotPath;
		unsigned int gameTime = 0;
		bool isRunning;
		bool isRenderingText = false;
		std::vector<SDL_Joystick*> joysticks;
		static bool toggledFullscreen;
};


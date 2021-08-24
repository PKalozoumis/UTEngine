#include "Game.h"
#include "SDL.h"
#include "SDL_image.h"
#include "TextureManager.h"
#include <iostream>
#include <iomanip>
#include "Tile.h"
#include "Tileset.h"
#include "Room.h"
#include "functions.h"
#include "color.h"
#include "ECS.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include <string>
#include "Menu.h"
#include "ColliderComponent.h"
#include "Text.h"
#include "Registry.h"
#include <map>
#include "SDL_ttf.h"
#include <fstream>
#include "json.hpp"
#include "Controller.h"
#include <cstdlib>
#include <ctime>
#include <filesystem>

#pragma warning(disable : 4996) //Allows me to get appdata path with getenv

Registry<std::string, TTF_Font*> Game::fontRegistry("Font Registry");
Registry<std::string, Tile*> Game::tileRegistry("Tile Registry");
Registry<std::string, Tileset*> Game::tilesetRegistry("Tileset Registry");
Registry<std::string, Room*> Game::roomRegistry("Room Registry");

SDL_Window* Game::window = nullptr;
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
Manager Game::manager;
Entity& Game::player = manager.addEntity();
SDL_Rect Game::camera = {0,0,0,0};
Room* Game::currentRoom = nullptr;
Menu Game::menu;
bool Game::toggledFullscreen = false;
int Game::xbor = 160;
int Game::ybor = 120;

Text* text;

Game::Game(void){} 
Game::~Game(void){}

void Game::loadFonts(void)
{
	nlohmann::json fontArray = jsonLoad("assets/data/fonts.json")["fonts"];

	for (int i = 0; i < fontArray.size(); i++)
	{
		std::string name = jsonToString(fontArray[i]["name"]);
		std::string path = jsonToString(fontArray[i]["filename"]);

		path = "assets/fonts/" + path;

		fontRegistry.registration(name, TTF_OpenFont(path.c_str(), fontArray[i]["size"]));
	}
}

void Game::loadRooms(void)
{
	nlohmann::json roomArray = jsonLoad("assets/data/rooms.json")["rooms"];

	for (int id = 0; id < roomArray.size(); id++)
	{
		std::string filename = jsonToString(roomArray[id]["filename"]);

		roomRegistry.registration(filename, new Room(id));
	}
}

void Game::loadJoysticks(void)
{
	std::cout << "\n" << SDL_NumJoysticks() << " gamepad(s) were found:" << std::endl;

	for (SDL_Joystick* joystick : joysticks)
		SDL_JoystickClose(joystick);

	joysticks.clear();

	for (int i = 0; i < SDL_NumJoysticks(); i++)
	{
		std::cout << "   " << SDL_JoystickNameForIndex(i) << std::endl;
		joysticks.push_back(SDL_JoystickOpen(i));
	}

	std::cout<<std::endl;
}

void Game::init(std::string title, int xpos, int ypos, int width, int height, bool fullscreen, std::string room)
{
	#pragma region ================================== INITIALIZATION ==================================
	int flags = 0;

	mainPath = std::string(getenv("LOCALAPPDATA"))+ "\\UTEngine\\";;
	stringReplace(mainPath, '\\', '/');

	//Main path
	if (std::filesystem::is_directory(mainPath))
	{
		std::cout << "Directory " + mainPath + " already exists" << std::endl;
	}
	else
	{
		std::filesystem::create_directory(mainPath);
	}

	//Screenshot path

	screenshotPath = mainPath + "Screenshots/";

	if (std::filesystem::is_directory(screenshotPath))
	{
		std::cout << "Directory " + screenshotPath + " already exists" << std::endl;
	}
	else
	{
		std::filesystem::create_directory(screenshotPath);
	}

	//Save path

	savePath = mainPath + "Saves/";

	if (std::filesystem::is_directory(savePath))
	{
		std::cout << "Directory " + savePath + " already exists" << std::endl;
	}
	else
	{
		std::filesystem::create_directory(savePath);
	}

	if (fullscreen) flags = SDL_WINDOW_FULLSCREEN_DESKTOP;

	//SDL
	if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "SUBSYSTEMS INITIALIZED SUCCESSFULLY" << std::endl;

		//Window
			window = SDL_CreateWindow(title.c_str(), xpos, ypos, width, height, flags);

			if (window)
			{
				std::cout << "WINDOW CREATED" << std::endl;
			}
	
		//Renderer
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_TARGETTEXTURE);

			if (renderer)
			{
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				SDL_RenderSetLogicalSize(renderer, 320, 240);
				std::cout << "RENDERER CREATED" << std::endl;
			}

		//Icon
			SDL_Surface* tempSurface = IMG_Load("assets/sprites/icon.png");
			SDL_SetWindowIcon(window, tempSurface);
			SDL_FreeSurface(tempSurface);

		isRunning = true;
	}
	else
	{
		std::cout << "SYSTEM INITIALIZATION FAILURE" << std::endl;
 		isRunning = false;
	}

	//TTF
	if (TTF_Init() == 0)
	{
		std::cout << "TTF INITIALIZED SUCCESSFULLY" << std::endl;
	}
	else
	{
		std::cout << "TTF INITIALIZATION FAILURE" << std::endl;
		isRunning = false;
	}

	loadJoysticks();

	#pragma endregion

	#pragma region ================================== REGISTRIES ==================================

	loadFonts();
	loadRooms();

	tileRegistry.registration("tile_air.png", new Tile("assets/sprites/tiles/tileset_air.json", 0));

	currentRoom = roomRegistry[room];

	#pragma endregion

	#pragma region ==================================== CAMERA ====================================

	camera.x = 0;
	camera.y = 0;
	camera.w = currentRoom->getWidth();
	camera.h = currentRoom->getHeight();

	#pragma endregion

	#pragma region =========================== PLAYER INITIALIZATION ===========================

	player.setPlayer(true);

	player.addComponent<TransformComponent>();
	player.addComponent<SpriteComponent>("assets/sprites/player/spr_sussy.png", xcenter, ycenter);
	player.addComponent<ColliderComponent>();

	player.getComponent<TransformComponent>().setForcedHeight(player.getComponent<SpriteComponent>().getImageHeight());
	player.getComponent<TransformComponent>().setForcedWidth(player.getComponent<SpriteComponent>().getImageWidth());
	player.getComponent<ColliderComponent>().setY(16);

	if (std::filesystem::exists(savePath + "playerPos.json"))
	{
		nlohmann::json j = jsonLoad(savePath + "playerPos.json");
		int px = j["x"];
		int py = j["y"];
		player.getComponent<TransformComponent>().setPos(px, py);
	}

	#pragma endregion

	Controller::init();

	#pragma region =========================== TEXT TESTING ===========================

	std::string testStr;

	//testStr = "* Long ago, two races ruled over EARTH: HUMANS and MONSTERS. One day, war broke out between the two races.";
	//testStr = "* According to all known laws of aviation, there is no way a bee should be able to fly. Its wings are too small to get its fat little body off the ground. The bee, of course, flies anyway because bees don't care what humans think is impossible. Yellow, black. Yellow, black. Yellow, black. Yellow, black. Ooh, black and yellow! Let's shake it up a little. Barry! Breakfast is ready! Ooming! Hang on a second. Hello? - Barry? - Adam? - Oan you believe this is happening?";
	//testStr = "* What's so funny about Sussus Amogus?";
	//testStr = "* Sus.";
	//testStr = "According to all known laws of aviation, there is no way a bee ";
	//testStr = "* This is text. And this, is a bigger text. This, however, is an even bigger text. And now this, even bigger. And this is now a ton bigger, see? The question is, how big can it get? Is this too big? Is this too small? Will the system break? Will it not? I am not sure. Pogchamp.";
	//testStr = "* It's better to cum in the shower, than to shower in the cum.                                           -Albert Einstein";
	//testStr = "* The phrase \"it's just a game\" is such a weak mindset. You are ok with what happened, losing, imperfection of a craft. When you stop getting angry after losing, you've lost twice. There's always something important to learn, and always room for improvement, never settle";
	//testStr = "* To be fair, you have to have a very high IQ to understand Rick and Morty. The humor is extremely subtle, and without a solid grasp of theoretical physics most of the jokes will go over a typical viewer's head. There's also Rick's nihilistic outlook, which is deftly woven into his characterisation - his personal philosophy draws heavily from Narodnaya Volya literature, for instance. The fans understand this stuff; they have the intellectual capacity to truly appreciate the depths of these jokes, to realize that they're not just funny- they say something deep about LIFE. As a consequence people who dislike Rick and Morty truly ARE idiots- of course they wouldn't appreciate, for instance, the humour in Rick's existencial catchphrase \"Wubba Lubba Dub Dub,\" which itself is a cryptic reference to Turgenev's Russian epic Fathers and Sons I'm smirking right now just imagining one of those addlepated simpletons scratching their heads in confusion as Dan Harmon's genius unfolds itself on their television screens. What fools... how I pity them. And yes by the way, I DO have a Rick and Morty tattoo. And no, you cannot see it. It's for the ladies' eyes only- And even they have to demonstrate that they're within 5 IQ points of my own (preferably lower) beforehand.";
	//testStr = "* According to YouTube statistics, only a small percentage of people that watch my videos are actually subscribed, so if you end up liking this video, consider subscribing, it's free, and you can always change your mind. Enjoy the video.";
	//testStr = "* I suck his dick with a smile for hours at a time. Stare at his nutsack while I hold back my cum tonight. And when he ask me what position I say, \"Doggystyle\". (And when they ask me what position I say, \"Doggystyle\"). But the fact is. I can never get off of his fat dick. And all that they can ask is (Ask is, ask is). \"I just wanna smack it\". (I just wanna smack it)";
	//testStr = "* STOP POSTING ABOUT AMONG US! I'M TIRED OF SEEING IT! My friends on TikTok send me memes, on discord it's fucking memes... I was in a server, right? And ALL of the channels are just Among Us stuff! I-i showed my champion underwear to my girlfriend and the logo I flipped it and i said, \"Hey babe, when the underwear is SUS, HAHA! DING DING DING DING DING DING DING, DING DING DING!\" I fuckin looked at a trash can, I said \"THATS A BIT SUSSY!\" I looked at my penis, I think of the astronauts helmet, and I go \"penis? MORE LIKE PENSUS! AAAAAAAAAAAAAAAAAAAAAAA\"";
	//testStr = "* I am a concerned mother with a 13 year old child and I am here to seek help regarding my son. Last week when we went to the supermarket, my son pointed to a red trash can and started jumping around screaming \"THAT'S AMONG US! THAT TRASH CAN IS SUS! RED IS THE IMPOSTOR!\" As soon as he did that, the manager told us to leave. I told him that my son is just excited about something, and apologised. But the manager still told us to leave so I picked up the red trash can that my son was going crazy over and threw it on the managers head. Then my son shouted \"DEAD BODY REPORTED.\" Can someone please tell me what on earth is wrong with him?";
	//testStr = "* Based? Based on what? In your dick? Please shut the fuck up and use words properly you fuckin troglodyte, do you think God gave us a freedom of speech just to spew random words that have no meaning that doesn't even correllate to the topic of the conversation? Like please you always complain about why no one talks to you or no one expresses their opinions on you because you're always spewing random shit like poggers based cringe and when you try to explain what it is and you just say that it's funny like what? What the fuck is funny about that do you think you'll just become a stand-up comedian that will get a standing ovation just because you said \"cum\" in the stage? HELL NO YOU FUCKIN IDIOT, so please shut the fuck up and use words properly you dumb bitch";
	//testStr = "* Ok, 19 dollar fortnite card, who wants it? And yes i'm giving it away. Remember, share! share! share! And trolls, don't get blocked!";
	//testStr = "* Ok so I am ultimately PISSED OFF RIGHT NOW because my STUPID INSENSITIVE BIGOT OF A SCIENCE TEACHER WON'T COVER THE SKELETON IN OUR CLASSROOM!!!! ive told him THOUSANDS of TIMES that i have severe anxiety from sans and ive actually developed ptsd from the sans fight and i have to carry around an inhaler everywhere i go now because when i see bones or the color blue i start hyperventilating because of panic then if i don't take my inhaler it turns into a ptsd episode and i already had to be sent home 3 TIMES BECAUSE THE SKELETON IN MY SCIENCE CLASS TRIGGERED ME!!!!! AND HE WON'T COVER IT!!!!!!!!! like?????? i don't know what to do ive tried talking about it to the councilors but they said my condition isnt real???? like um YEAH IT IS??? i would know????????? cause i wake up screaming and in tears each night because i have a reaccuring nightmare where SANS TELLS ME I'M GOING TO HAVE A BAD TIME THEN HE HAS THE FUCKING DECENCY TO TELL ME I'VE DIED TEN TIMES, AND THAT I HAVE NO FRIENDS!! YOU KNOW HOW MUCH THAT FUCKING TRIGGERS ME???????? and it just PISSES ME OFF how the school doesn't even CARE THAT I AM ON THE BRINK OF ODING BECAUSE OF THIS!!!";
	//testStr = "* I am out of copypastas, so this should be enough testing for today :)";
	//testStr = "Oh, yeah! You gotta get schwifty. You gotta get schwifty in here. It's time to get schwifty. Oh-oh. You gotta get schwifty. Oh, yeah! Take off your pants and your panties. Shit on the floor. Time to get Schwifty in here. Gotta shit on the floor. I'm Mr. Bulldops. I'm Mr. Bulldops. Take a shit on the floor. Take off your panties and your pants. It's time to get schwifty in here. New song \"schwifty\" Double X, schwifty song comin'at ya. It's the schwif-schwifty. Hey, take your pants off. It's schwifty time today.";

	text = new Text(2, 0 , "Among Us", "fnt_main", c_white, full, c_red, 1, 1, true);
	isRenderingText = true;

	#pragma endregion
}

void Game::handleEvents(void)
{
	SDL_JoystickEventState(SDL_ENABLE);
	Controller::update();
	SDL_PollEvent(&event);

	switch(event.type)
	{
		/*case SDL_JOYAXISMOTION:
		{
			if (event.jaxis.axis == 0)
			{
				if ((event.jaxis.value > -8000) && (event.jaxis.value < 8000)) 
				{
					player.getComponent<TransformComponent>().setVx(0);
				}
				else
				{
					if ((event.jaxis.value > 0) && (player.getComponent<TransformComponent>().getVx() != -1))
					{
						player.getComponent<TransformComponent>().setVx(1);
					}
					else if (event.jaxis.value < 0)
					{
						player.getComponent<TransformComponent>().setVx(-1);
					}
				}
			}
		}
		break;*/

		case SDL_QUIT: isRunning = false; break;
		default: break;
	}
}

void Game::update(void)
{
	#pragma region ================================== INPUT ==================================

	#pragma region Debug

	if (Controller::buttonPressed(SDL_SCANCODE_1))
		fontRegistry.print();

	if (Controller::buttonPressed(SDL_SCANCODE_2))
		tileRegistry.print();

	if (Controller::buttonPressed(SDL_SCANCODE_3))
		tilesetRegistry.print();

	if (Controller::buttonPressed(SDL_SCANCODE_4))
		roomRegistry.print();

	if (Controller::buttonPressed(SDL_SCANCODE_J))
		loadJoysticks();

	if (Controller::buttonPressed(SDL_SCANCODE_T))
		text->setOutlineColor(c_lime);

	if (Controller::buttonPressed(SDL_SCANCODE_S)) //Save the game
	{
		int px = player.getComponent<TransformComponent>().getX();
		int py = player.getComponent<TransformComponent>().getY();

		std::ofstream savefile(savePath + "playerPos.json");

		nlohmann::json j;
		j["x"] = px;
		j["y"] = py;
		savefile << j;

		savefile.close();
	}

	if (Controller::buttonPressed(SDL_SCANCODE_D))
	{
		if (isRenderingText)
		{
			delete text;
			isRenderingText = false;
		}
	}

	if (Controller::buttonPressed(SDL_SCANCODE_8))
		roomGotoPrevious();

	if (Controller::buttonPressed(SDL_SCANCODE_9)) 
		roomGotoNext();

	#pragma endregion

	#pragma region Player Input

	if ((Controller::button("keyRight")) && (player.getComponent<TransformComponent>().getVx() != -1))
		player.getComponent<TransformComponent>().setVx(1);
	else if (Controller::button("keyLeft"))
		player.getComponent<TransformComponent>().setVx(-1);
	else player.getComponent<TransformComponent>().setVx(0);

	if ((Controller::button("keyDown")) && (player.getComponent<TransformComponent>().getVy() != -1))
		player.getComponent<TransformComponent>().setVy(1);
	else if (Controller::button("keyUp"))
		player.getComponent<TransformComponent>().setVy(-1);
	else player.getComponent<TransformComponent>().setVy(0);

	#pragma endregion

	#pragma region Screenshot Tool

	if (Controller::buttonPressed("keyScreenshot"))
	{
		SDL_GetRendererOutputSize(renderer, &screenshotWidth, &screenshotHeight);
		SDL_Surface *screenshot = SDL_CreateRGBSurface(0, screenshotWidth, screenshotHeight, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
		SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ARGB8888, screenshot->pixels, screenshot->pitch);
		std::string screenName = "Screenshot_" + std::to_string(std::time(nullptr)) + ".png";
		std::string dir = screenshotPath + screenName;
		SDL_SaveBMP(screenshot, dir.c_str());
		SDL_FreeSurface(screenshot);

		std::cout << "Saved screenshot as " + screenName << std::endl;
	}
	#pragma endregion

	#pragma region Fullscreen Toggle

	if (Controller::buttonPressed("keyFullscreen"))
	{
		if ((SDL_GetWindowFlags(window)&SDL_WINDOW_FULLSCREEN_DESKTOP) == 0)
		{
			SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
		}
		else  SDL_SetWindowFullscreen(window, 0);

		toggledFullscreen = true;
	}

	#pragma endregion

	//Game go oof
	if (Controller::buttonPressed("keyEnd"))
		isRunning = false;

	#pragma endregion
	
	#pragma region ================================== PLAYER ==================================

	int frame = player.getComponent<SpriteComponent>().getImageIndex();
	static std::string dir = "front";

	if (player.getComponent<TransformComponent>().getVy() == 0)
	{
		if (player.getComponent<TransformComponent>().getVx() == 1) 
		{
			dir = "right";
		}
		else if (player.getComponent<TransformComponent>().getVx() == -1)
		{
			dir = "left";
		}
	}

	if (player.getComponent<TransformComponent>().getVx() == 0)
	{
		if (player.getComponent<TransformComponent>().getVy() == 1)
		{
			dir = "front";
		}
		else if (player.getComponent<TransformComponent>().getVy() == -1)
		{
			dir = "back";
		}
	}

	SDL_Rect playerCollider = *player.getComponent<ColliderComponent>().getCollider();
	playerCollider.x += 2*player.getComponent<TransformComponent>().getVx();
	playerCollider.y += 2*player.getComponent<TransformComponent>().getVy();

	/*if (AABB(playerCollider, *wall.getComponent<ColliderComponent>().getCollider()))
	{
		std::cout<<"COLLISION DETECTED"<<std::endl;
		player.getComponent<TransformComponent>().setV(0,0);
	}*/

	player.getComponent<SpriteComponent>().setSprite("assets/sprites/player/spr_player_" + dir + std::to_string(frame) + ".png");
	//std::cout<<"Frame: "<<frame<<std::endl;

	#pragma endregion

	#pragma region ================================== CAMERA ==================================

	/*camera.x = player.getComponent<TransformComponent>().getX() - 160;
	camera.y = player.getComponent<TransformComponent>().getY() - 120;
	camera.w = currentRoom->getWidth();
	camera.h = currentRoom->getHeight();

	if (camera.x < 0) camera.x = 0;
	if (camera.y < 0) camera.y = 0;
	if (camera.x > camera.w/2) camera.x = camera.w/2;
	if (camera.y > camera.h/2) camera.y = camera.h/2;*/

	camera.w = currentRoom->getWidth();
	camera.h = currentRoom->getHeight();

	int px = player.getComponent<TransformComponent>().getX();
	int py = player.getComponent<TransformComponent>().getY();

	if (camera.w > 320)
	{
		if (px >= xbor)
		{
			if ((px <= camera.w-xbor))
			{
				camera.x = px - xbor;
			}
			else camera.x = camera.w - 2*xbor;
		}
		else camera.x = 0;
	}

	if (camera.h > 240)
	{
		if (py >= ybor)
		{
			if ((py <= camera.h-ybor))
			{
				camera.y = py - ybor;
			}
			else camera.y = camera.h - 2*ybor;
		}
		else camera.y = 0;
	}

	#pragma endregion

	manager.update();

	if (isRenderingText)
		text->update();
	gameTime++;

	//std::cout << "(" << px << ", " << py << ")" << std::endl;
}

void Game::roomGoto(int roomID)
{
	currentRoom = roomRegistry.get(roomID);
}

void Game::roomGotoNext(void)
{
	if (currentRoom->getId() + 1 < roomRegistry.size())
	{
		currentRoom = roomRegistry.get(currentRoom->getId() + 1);
		camera.x = 0;
		camera.y = 0;
	}
}

void Game::roomGotoPrevious(void)
{
	if (currentRoom->getId() - 1 >= 0)
	{
		currentRoom = roomRegistry.get(currentRoom->getId() - 1);
		camera.x = 0;
		camera.y = 0;
	}
}

bool Game::getFullscreen(void)
{
	return SDL_GetWindowFlags(window)&SDL_WINDOW_FULLSCREEN_DESKTOP;
}

bool Game::getToggledFullscreen(void)
{
	return toggledFullscreen;
}

void Game::render(void)
{
	SDL_RenderClear(renderer);

	currentRoom->drawRoom();
	manager.draw();
	menu.draw();
	
	//drawRectangleColor(-camera.x, - camera.y, currentRoom->getWidth() - camera.x, currentRoom->getHeight() - camera.y, 1, c_lime);
	//drawRectangleColor(160 - camera.x, 120 - camera.y, currentRoom->getWidth() - 160 - camera.x, currentRoom->getHeight() - 120 - camera.y, 1, c_white);

	//drawMenuBox(16, 160, 305, 236);
	//drawMenuBox(16, -10, 305, 300);

	if (isRenderingText)
		text->draw();

	drawResetColor();

	SDL_RenderPresent(renderer);
}

void Game::endFrame(void)
{
	toggledFullscreen = false;
}

void Game::clean(void)
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	std::cout << "CLEANED" << std::endl;
}

bool Game::running(void)
{
	return isRunning;
}

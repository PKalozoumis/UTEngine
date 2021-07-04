#include "Game.h"
#include "SDL.h"
#include "SDL_image.h"
#include "TextureManager.h"
#include "GameObject.h"
#include <iostream>

using namespace std;

GameObject* objPlayer = NULL;

Game::Game(){} 
Game::~Game(){}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		cout<< "SUBSYSTEMS INITIALIZED" << endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		if (window)
		{
			cout<<"WINDOW CREATED"<<endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);

		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			cout<<"RENDERER CREATED"<<endl;
		}

		isRunning = true;
	}
	else isRunning = false;

	objPlayer = new GameObject("assets/sprites/player/spr_player_front0.png", renderer);
}

void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch(event.type)
	{
		case SDL_QUIT: isRunning = false; break;
		default: break;
	}
}

void Game::update()
{
	objPlayer->update();
}

void Game::render()
{
	SDL_RenderClear(renderer);
	objPlayer -> render();
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	cout<<"CLEANED"<<endl;
}

bool Game::running()
{
	return isRunning;
}

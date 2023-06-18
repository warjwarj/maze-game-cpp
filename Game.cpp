#include <iostream>
#include <stdlib.h>
#include <exception>

#include <SDL.h>

#include "Game.h"

SDL_Window* Game::gameWindow = nullptr;
SDL_Renderer* Game::gameRenderer = nullptr;

bool Game::init()
{
	// Initialisation flag
	bool success = true;

	// initialise SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialise! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		// Create window
		gameWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gameWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			// Create renderer for window
			gameRenderer = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gameRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				// initialise renderer color
				SDL_SetRenderDrawColor(gameRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			}
		}
	}
	return success;
};

void Game::close()
{
	// Destroy window	
	SDL_DestroyRenderer(gameRenderer);
	SDL_DestroyWindow(gameWindow);

	gameWindow = NULL;
	gameRenderer = NULL;

	// Quit SDL subsystems
	SDL_Quit();
};
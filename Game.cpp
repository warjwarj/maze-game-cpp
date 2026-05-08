#include <iostream>
#include <stdlib.h>
#include <exception>

#include <SDL.h>

#include "Game.h"

Game::Game(int h, int w)
{
	int smallerDimension = h > w ? w : h;
	screenWidth = smallerDimension * 0.8;
	screenHeight = smallerDimension * 0.8;

	gameWindow = nullptr;
	gameRenderer = nullptr;
	gridHeight = 15;
	gridWidth = 15;
	cellSize = 36;
}

bool Game::init()
{
	bool success = true;
	// Create window
	gameWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->screenWidth, this->screenHeight, SDL_WINDOW_SHOWN);
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
	return success;
};

void Game::close()
{
	SDL_DestroyRenderer(gameRenderer);
	SDL_DestroyWindow(gameWindow);

	gameWindow = nullptr;
	gameRenderer = nullptr;

	SDL_Quit();
};
#include <iostream>
#include <stdlib.h>
#include <exception>

#include <SDL.h>
#include <SDL_ttf.h>

#include "Game.h"
#include "Grid.h"
#include "Player.h"
#include "CountdownTimer.h"

Game::Game(int h, int w, int startSecs) :
	timer(startSecs)
{
	int smallerDimension = h > w ? w : h;
	screenWidth = smallerDimension * 0.8;
	screenHeight = smallerDimension * 0.8;

	gameWindow = nullptr;
	gameRenderer = nullptr;
	gameFont = nullptr;

	gridHeight = 13;
	gridWidth = 13;
	cellSize = screenHeight / 25;

	innerWindowPositionX = screenWidth - (screenWidth - (gridWidth * cellSize)) / 2;
	innerWindowPositionY = screenWidth - (screenHeight - (gridHeight * cellSize)) / 2;

	mazesSolved = 0;
}

bool Game::init()
{
	// init ttf font stuff
	if (TTF_Init() == -1) {
		printf("TTF_Init failed: %s\n", TTF_GetError());
		return false;
	}

	// open a font
	gameFont = TTF_OpenFont("C:\\Windows\\Fonts\\Arial.ttf", 20);
	if (gameFont == NULL)
	{
		printf("TTF_OpenFont failed: %s\n", TTF_GetError());
		return false;
	}

	// Create window
	gameWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->screenWidth, this->screenHeight, SDL_WINDOW_SHOWN);
	if (gameWindow == NULL)
	{
		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	// Create renderer for window
	gameRenderer = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_ACCELERATED);
	if (gameRenderer == NULL)
	{
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	return true;
};

int Game::gameLoop(Grid& grid, Player& player)
{
	int quit = 0;
	SDL_Event e;
	while (quit == 0)
	{
		// refresh screen
		SDL_RenderPresent(this->gameRenderer);

		// clear event queue
		while (SDL_PollEvent(&e) != 0)
			captureInput(&quit, e, player, grid);

		// reset colour, clear renderer and redraw game
		SDL_SetRenderDrawColor(gameRenderer, 0, 0, 0, 0);
		SDL_RenderClear(gameRenderer);
		grid.redrawCells();
		loadGameStats();

		// yaaay! level finished!!
		if (player.atfinish())
		{
			mazesSolved += 1;

			increaseGridSize(grid);

			timer.addSeconds(2);
			std::cout << player.atfinish() << std::endl;
			break;
		}
	}
	return quit;
}

void Game::loadGameStats()
{
	std::string label = "Solved: " + std::to_string(mazesSolved) + " | " + std::to_string(timer.getSeconds());
	int textW = 0, textH = 0;
	TTF_SizeText(gameFont, label.c_str(), &textW, &textH);
	renderText(label, 10, 10);
}

void Game::renderText(std::string& text, int x, int y)
{
	SDL_Surface* surface = TTF_RenderText_Solid(gameFont, text.c_str(), WHITE);
	if (!surface) return;
	SDL_Texture* texture = SDL_CreateTextureFromSurface(gameRenderer, surface);

	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = surface->w;
	dst.h = surface->h;
	SDL_RenderCopy(gameRenderer, texture, NULL, &dst);

	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}

void Game::captureInput(int* quit, SDL_Event& e, Player& player, Grid& grid)
{
	switch (e.type)
	{
	case SDL_QUIT:
		*quit = 1;
		break;
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
			if (e.key.keysym.mod & KMOD_SHIFT)
			{
				player.move(up_max, grid.grid);
				break;
			}
			else
			{
				player.move(up_one, grid.grid);
				break;
			}
		case SDLK_DOWN:
			if (e.key.keysym.mod & KMOD_SHIFT)
			{
				player.move(down_max, grid.grid);
				break;
			}
			else
			{
				player.move(down_one, grid.grid);
				break;
			}
		case SDLK_LEFT:
			if (e.key.keysym.mod & KMOD_SHIFT)
			{
				player.move(left_max, grid.grid);
				break;
			}
			else
			{
				player.move(left_one, grid.grid);
				break;
			}
		case SDLK_RIGHT:
			if (e.key.keysym.mod & KMOD_SHIFT)
			{
				player.move(right_max, grid.grid);
				break;
			}
			else
			{
				player.move(right_one, grid.grid);
				break;
			}
		default:
			// no arrow keys pressed
			std::cout << "press an arow key to move" << std::endl;
			break;
		}
	}
}

void Game::close()
{
	TTF_CloseFont(gameFont);
	TTF_Quit();

	SDL_DestroyRenderer(gameRenderer);
	SDL_DestroyWindow(gameWindow);

	gameWindow = nullptr;
	gameRenderer = nullptr;

	SDL_Quit();
};

int Game::getCellSize(int increasedGridHeight, int maxGridHeight)
{
	int newCellSize = cellSize;
	if (increasedGridHeight > maxGridHeight)
		while ((newCellSize * gridHeight) > maxGridHeight)
			newCellSize -= 1;
	return newCellSize;
}

void Game::increaseGridSize(Grid& grid)
{
	int newWidth = gridWidth += 2;
	int newHeight = gridHeight += 2;

	// this depends on the grid being a square
	int increasedGridSize = newHeight * cellSize;
	int maxGridSize = getScreenHeight() * 0.8;

	if (increasedGridSize > maxGridSize)
		cellSize = getCellSize(increasedGridSize, maxGridSize);

	innerWindowPositionX = screenWidth - (screenWidth - (gridWidth * cellSize)) / 2;
	innerWindowPositionY = screenWidth - (screenHeight - (gridHeight * cellSize)) / 2;
}
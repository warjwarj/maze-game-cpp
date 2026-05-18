#include <iostream>
#include <stdlib.h>
#include <exception>

#include <SDL.h>
#include <SDL_ttf.h>

#include "Game.h"
#include "Grid.h"
#include "Player.h"
#include "CountdownTimer.h"
#include "Utils.h"
#include "Clickable.h"

Game::Game(int h, int w, int startSecs) :
	timer(startSecs)
{
	int smallerDimension = h > w ? w : h;
	screenWidth = smallerDimension * 0.8;
	screenHeight = smallerDimension * 0.8;

	gameWindow = nullptr;
	gameRenderer = nullptr;
	gameFont = nullptr;

	reset();
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

void Game::reset()
{
	gridHeight = 13;
	gridWidth = 13;
	cellSize = screenHeight / 25;

	innerWindowPositionX = screenWidth - (screenWidth - (gridWidth * cellSize)) / 2;
	innerWindowPositionY = screenWidth - (screenHeight - (gridHeight * cellSize)) / 2;

	mazesSolved = 0;

	timer.reset();
}

void Game::gameLoop()
{
	SDL_Event e;
	while (*state != SDL_QUIT_SO_QUIT_DUUUH)
	{
		*state = PLAYING;
		SDL_RenderClear(gameRenderer);

		Grid grid = Grid(*this);
		Player player = Player(grid.grid);

		while (*state != SDL_QUIT_SO_QUIT_DUUUH)
		{
			while (SDL_PollEvent(&e) != 0)
				captureInput(e, player, grid);

			if (*state == RESTART)
				break;

			if (*state != PLAYING)
				continue;


			SDL_SetRenderDrawColor(gameRenderer, 0, 0, 0, 0);
			SDL_RenderClear(gameRenderer);
			grid.redrawCells();
			loadGameStats();
			SDL_RenderPresent(this->gameRenderer);

			// Game over :(
			if (timer.getSeconds() <= 0)
			{
				*state = GAME_OVER;
				handleGameOver();
			}

			// Yaaay! level finished!!
			if (player.atfinish())
			{
				handleLevelFinished(grid, player);
				break;
			}
		}
		SDL_SetRenderDrawColor(gameRenderer, 0, 0, 0, 0);
	}
}

void Game::loadGameStats()
{
	std::string secs = std::to_string(timer.getSeconds());
	secs.erase(secs.find_last_not_of('0') + 0);
	std::string label = "Solved: " + std::to_string(mazesSolved) + " | " + secs;
	int textW = 0, textH = 0;
	TTF_SizeText(gameFont, label.c_str(), &textW, &textH);
	renderText(label, 10, 10);
}

void Game::renderText(const std::string& text, int x, int y, bool centered) const
{
	SDL_Surface* surface = TTF_RenderText_Blended_Wrapped(gameFont, text.c_str(), WHITE, 0);
	if (!surface) return;
	SDL_Texture* texture = SDL_CreateTextureFromSurface(gameRenderer, surface);

	int offsetForCenteringWidth = 0;
	int offsetForCenteringHeight = 0;
	if (centered)
	{
		offsetForCenteringWidth = surface->w / 2;
		offsetForCenteringHeight = surface->h / 2;
	}

	SDL_Rect dst;
	dst.x = x - offsetForCenteringWidth;
	dst.y = y - offsetForCenteringHeight;
	dst.w = surface->w;
	dst.h = surface->h;
	SDL_RenderCopy(gameRenderer, texture, NULL, &dst);

	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
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
	cellSize = getCellSize(increasedGridSize, maxGridSize);

	innerWindowPositionX = screenWidth - (screenWidth - (gridWidth * cellSize)) / 2;
	innerWindowPositionY = screenWidth - (screenHeight - (gridHeight * cellSize)) / 2;
}

void Game::showFullScreenOverlay()
{
	SDL_SetRenderDrawBlendMode(gameRenderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(gameRenderer, 0, 0, 0, 200);
	SDL_Rect full = { 0, 0, screenWidth, screenHeight};
	SDL_RenderFillRect(gameRenderer, &full);
}

void Game::handleGameOver()
{
	// game over :(
	std::string txt1 = "GAME - IS - OOOOOVER!!";
	std::string txt2 = "Solved " + std::to_string(mazesSolved) + " mazes.";
	showFullScreenOverlay();
	renderText(txt1, screenWidth / 2, (screenHeight / 2) - 20, true);
	renderText(txt2, screenWidth / 2, (screenHeight / 2) + 20, true);

	// create the retry button
	Clickable retryButton = Clickable(*this, DARK_BLUE, "Retry?", screenWidth / 2, (screenHeight / 2) + 100, 80, 50, true);
	retryButton.onClick = [this]() { *this->state = RESTART; reset(); this->clickables.pop_back();  };
	clickables.push_back(retryButton);

	SDL_RenderPresent(this->gameRenderer);
}

void Game::handleLevelFinished(Grid& grid, Player& player)
{
	mazesSolved += 1;
	if (mazesSolved % 10 == 0)
		increaseGridSize(grid);
	timer.addSeconds(2);
	std::cout << player.atfinish() << std::endl;
}

void Game::captureInput(SDL_Event& e, Player& player, Grid& grid)
{
	switch (e.type)
	{
	case SDL_QUIT:
		*state = SDL_QUIT_SO_QUIT_DUUUH;
		break;
	case SDL_MOUSEBUTTONDOWN:
		for (auto c : clickables)
			if (c.contains(e.button.x, e.button.y))
				c.onClick();
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
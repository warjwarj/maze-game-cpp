#include <iostream>
#include <string>
#include <cmath>

#include <SDL.h>
#include <SDL_ttf.h>

#include "Game.h"
#include "Grid.h"
#include "Player.h"

int main(int argc, char* args[])
{
	// initialise SDl
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialise! SDL Error: %s\n", SDL_GetError());
		return 0;
	}
	SDL_DisplayMode dm;
	SDL_GetCurrentDisplayMode(0, &dm);

	// This is where we hold all the game logic
	Game game(dm.h, dm.w, 30);

	// Start up SDL and create window
	if (!game.init())
	{
		std::cout << "Failed to init!" << std::endl;
		return 0;
	}

	bool quit = 0;
	while (quit == 0)
	{
		SDL_RenderClear(game.gameRenderer);
		game.loadGameStats();

		Grid grid = Grid(game);
		Player player = Player(grid.grid);
		quit = game.gameLoop(grid, player);

		SDL_SetRenderDrawColor(game.gameRenderer, 0, 0, 0, 0);
	}
	// Free resources and close SDL
	game.close();
	return 0;
}
#include <iostream>
#include <string>
#include <cmath>

#include <SDL.h>

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
	Game game(dm.h, dm.w);

	// Start up SDL and create window
	if(!game.init())
		std::cout << "Failed to init!" << std::endl;
	else
	{
		bool quit = false;
		SDL_Event e;
		while (!quit)
		{
			Grid grid = Grid(game);
			Player player = Player(grid.grid);
			while (!quit)
			{
				SDL_RenderPresent(game.gameRenderer);
				while (SDL_PollEvent(&e) != 0)
				{
					switch (e.type)
					{
					case SDL_QUIT:

						quit = true;
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
					default:
						// no events
						break;
					}
				}
				if (player.atfinish())
				{
					std::cout << player.atfinish() << std::endl;
					break;
				}
			}
		}
	}
	// Free resources and close SDL
	game.close();
	return 0;
}
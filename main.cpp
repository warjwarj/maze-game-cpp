#include <iostream>
#include <string>
#include <cmath>

#include <SDL.h>

#include "Game.h"
#include "Structure.h"
#include "Movement.h"

int main(int argc, char* args[])
{
	// Start up SDL and create window
	if (!Game::init())
	{
		std::cout << "Failed to init!" << std::endl;
	}
	else
	{
		// Main loop flag
		bool quit = false;

		// Event handler
		SDL_Event e;

		//While application is running
		while (!quit)
		{
			// instantiate grid obj and create
			Grid grid = Grid();

			// player
			Player player = Player(grid.grid);

			while (!quit)
			{
				SDL_RenderPresent(Game::gameRenderer);

				// Handle events on queue until we get to end of queue
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
	Game::close();
	return 0;
}
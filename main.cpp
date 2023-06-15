#include <iostream>
#include <string>
#include <cmath>

#include <SDL.h>

#include "Game.h"
#include "Structure.h"
#include "Movement.h"

int main(int argc, char* args[])
{
	try
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

			// instantiate grid obj and create
			Grid grid = Grid();

			// player
			Player player = Player(grid.grid);

			//While application is running
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
							break;
						}
					default:

						// no events
						break;
					}
				}
			}
		}
	}
	// test for intentional error thrown when user quits game
	catch (StackUnwind errmsg) {
		std::cerr << errmsg.what() << std::endl;
		Game::close();
		return 0;
	}
	// Free resources and close SDL
	Game::close();
	return 0;
}
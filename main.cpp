#include <iostream>
#include <string>
#include <cmath>

#include <SDL.h>

#include "Game.h"
#include "Structure.h"

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

			//While application is running
			while (!quit)
			{
				SDL_RenderPresent(Game::gameRenderer);

				// Handle events on queue until we get to end of queue
				while (SDL_PollEvent(&e) != 0)
				{
					// User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
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
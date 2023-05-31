/*This source code copyrighted by Lazy Foo' Productions (2004-2022)
and may not be redistributed without written permission.*/

#include <SDL.h>
#include <stdio.h>
#include <string>
#include <cmath>

#include "Game.h"
#include "Structure.h"

/* TRY AND SEPERATE CONSTRUCTOR FROM INITIALISATION OF GRID + CELL */

int main(int argc, char* args[])
{
	// Start up SDL and create window
	if (!Game::init())
	{
		printf("Failed to initialise\n");
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
	// Free resources and close SDL
	Game::close();
	return 0;
}
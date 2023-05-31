#pragma once

#include <SDL.h>

struct Game
{
	// Screen dimension constants
	static const int SCREEN_WIDTH = 900;
	static const int SCREEN_HEIGHT = 900;

	// The game window we render to
	static SDL_Window* gameWindow;

	// The renderer
	static SDL_Renderer* gameRenderer;

	// Starts up SDL and creates window
	static bool init();

	// Frees media and shuts down SDL
	static void close();
};
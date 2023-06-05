#pragma once

#include <SDL.h>

class StackUnwind : public std::exception
{
private:

	std::string errmsg;

public:

	StackUnwind(const std::string& errmsg) : errmsg(errmsg) {  };

	virtual const char* what() const noexcept override
	{
		return errmsg.c_str();
	}
};

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

	// check if a user has quit the game
	static void checkQuit();

	// Frees media and shuts down SDL
	static void close();
};
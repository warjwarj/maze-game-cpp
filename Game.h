#pragma once

#ifndef GAME_H

#define GAME_H

#endif // !GAME_H

 
#include <exception>
#include <string>

#include <SDL.h>

// vector, a quantity that has both magnitude and direction.
// enum below describes the four directions that the player can move in,
// and also the two possible distances that they can travel in each direction,
// one cell, or as many as possible until they reach a wall.
enum Vector
{
	up_one,
	down_one,
	left_one,
	right_one,
	up_max,
	down_max,
	left_max,
	right_max,
	none
};

static SDL_Color BLACK = { 0, 0, 0 ,255 };
static SDL_Color WHITE = { 255, 255, 255 ,255 };
static SDL_Color RED = { 222, 90, 67 ,255 };
static SDL_Color DARK_BLUE = { 15, 99, 255 ,255 };
static SDL_Color GREY = { 92, 92, 92 ,255 };
static SDL_Color LIGHTER_GREY = { 145, 145, 145 ,255 };
static SDL_Color GREEN = { 28, 252, 3 ,255 };

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
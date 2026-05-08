#pragma once

#ifndef GAME_H

#define GAME_H

#endif // !GAME_H

 
#include <exception>
#include <string>

#include <SDL.h>

class Game
{
private:

	int screenWidth;
	int screenHeight;

public:

	int gridHeight;
	int gridWidth;
	int cellSize;

	SDL_Window* gameWindow;
	SDL_Renderer* gameRenderer;

	Game(int screenHeight, int screenWidth);

	bool init();
	void checkQuit();
	void close();
};
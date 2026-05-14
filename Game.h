#pragma once

#include <exception>
#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

#include "CountdownTimer.h"

class Grid;
class Player;

class Game
{
private:

	int screenWidth;
	int screenHeight;

	int innerWindowPositionX;
	int innerWindowPositionY;

	int mazesSolved;

public:

	int getMazesSolved() const { return mazesSolved; }
	int getinnerWindowPositionX() const { return innerWindowPositionX; }
	int getinnerWindowPositionY() const { return innerWindowPositionY; }
	int getScreenWidth() const { return screenWidth; }
	int getScreenHeight() const { return screenHeight; }

	int gridHeight;
	int gridWidth;
	int cellSize;

	SDL_Window* gameWindow;
	SDL_Renderer* gameRenderer;
	TTF_Font* gameFont;

	Game(int screenHeight, int screenWidth, int startSecs);

	bool init();
	void close();

	int gameLoop(Grid& grid, Player& player);
	void captureInput(int* quit, SDL_Event& e, Player& player, Grid& grid);
	void loadGameStats();	
	void renderText(std::string& text, int x, int y);
	void increaseGridSize(Grid& grid);
	int getCellSize(int increasedGridSize, int maxGridSize);

	CountdownTimer timer;
};
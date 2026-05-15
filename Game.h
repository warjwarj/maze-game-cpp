#pragma once

#include <exception>
#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

#include "CountdownTimer.h"

class Grid;
class Player;
enum GameState;

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

	void gameLoop(GameState* gs, Grid& grid, Player& player);
	void captureInput(GameState* quit, SDL_Event& e, Player& player, Grid& grid);
	void loadGameStats();
	void renderText(std::string& text, int x, int y, bool centerIt = false);
	void increaseGridSize(Grid& grid);
	int getCellSize(int increasedGridSize, int maxGridSize);
	void showFullScreenOverlay();

	CountdownTimer timer;
};
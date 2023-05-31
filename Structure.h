#pragma once
#pragma warning ( disable : 26495 )

#include <SDL.h>

class Cell
{
private:

	int cell_size = 36;
	int x;
	int y;

	SDL_Rect rect;
	SDL_Colour colour;

public:

	// TODO - make private, setter function
	bool wall = false;
	bool visited = false;
	bool finish = false;

	void draw(SDL_Colour colour);

	Cell(int x, int y, SDL_Colour colour);

	Cell() { /* default constructor to appease VS */ };
};

class Grid
{
private:

	// start dimensions, perfect for the 900 x 900 window
	static const int width = 25;
	static const int height = 25;

	// main grid 
	Cell grid[width][height];

public:

	Grid();
};
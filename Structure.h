#pragma once
#pragma warning ( disable : 26495 )

#include <SDL.h>

class Cell
{
	friend class Grid;

private:

	int cell_size = 36;
	int x;
	int y;

	bool wall = false;
	bool visited = false;
	bool finish = false;

	SDL_Rect rect;
	SDL_Colour colour;

	void draw(SDL_Colour colour);

	Cell(int x, int y, SDL_Colour colour);

	Cell() {}

};

class Grid
{
private:

	// start dimensions, perfect for the 900 x 900 window
	static const int width = 25;
	static const int height = 25;

	// main grid 
	Cell grid[width][height];

	void create();

	void maze();

public:

	Grid()
	{	
		create();
		//maze();
	};

};


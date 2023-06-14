#pragma once
#pragma warning ( disable : 26495 )

#include <map>

#include <SDL.h>

#include "Game.h"

//1x900
//2x450
//3x300
//4x225
//5x180
//6x150
//9x100
//10x90
//12x75
//15x60
//18x50
//20x45
//25x36
//30x30
//36x25
//45x20
//50x18
//60x15
//75x12
//90x10
//100x9
//150x6
//180x5
//225x4
//300x3
//450x2
//900x1

class Cell
{
	friend class Grid;

private:

	int cell_size = 36;

	bool wall = false;
	bool visited = false;
	bool finish = false;

	SDL_Rect rect;
	SDL_Colour colour;

	Cell(int x, int y, SDL_Colour colour);

public:

	Cell() {}

	void draw(SDL_Colour colour);

	bool iswall() { return this->wall;  }

	int x;
	int y;
};

class Grid
{
	friend class Player;

private:

	// start dimensions, perfect for the 900 x 900 window
	static const int width = 25;
	static const int height = 25;

	void create();

	void maze();


public:

	// main grid
	Cell grid[width][height];

	Grid()
	{
		create();
		maze();
	};
};
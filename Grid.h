#pragma once

#include "Cell.h"

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

#pragma once

#include <vector>
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
	std::vector<std::vector<Cell>> grid;

	Grid()
	{
		create();
		maze();
	};
};

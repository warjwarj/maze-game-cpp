#pragma once

#include <vector>
#include "Cell.h"

class Grid
{
	friend class Player;

private:

	const Game& game;
	int width;
	int height;

	void create();
	void maze();

public:

	std::vector<std::vector<Cell*>> grid;

	Grid(const Game& game);

	void redrawCells();
	void setDimensions(int width, int height, int cellSize);
};

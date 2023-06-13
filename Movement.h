#pragma once

#include <map>

#include "Structure.h"
#include "Game.h"

class Player
{
private:

	Cell cell;

	Cell** grid;

	// dictionary of cells the player can move to
	std::map<Vector, Cell> movements;

	// helper function used in getMovements
	Cell getFurthestCellInDirection(Vector vector, Cell** grid, Cell cell);

	// check that we can move in the specified direction
	void getMovements(Vector vector, Cell** grid);

	// guess what
	void move(Vector vector);

public:

	Player(Cell (*grid)[Grid::width][Grid::height]);
};
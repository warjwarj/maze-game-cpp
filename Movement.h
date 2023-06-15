#pragma once

#include <map>

#include "Structure.h"
#include "Game.h"

class Player
{
private:

	Cell cell;

	// dictionary of cells the player can move to
	std::map<Vector, Cell> movements;

	// helper function used in getMovements
	Cell getFurthestReachableCellInDirection(Vector vector, Cell grid[][Grid::height]);

	// check that we can move in the specified direction
	void getMovements(Cell grid[][Grid::height]);

public:

	// guess what
	void move(Vector vector, Cell grid[][Grid::height]);

	// representation of a 2d array in a function param list, dont need to specify the length the first dimension, as it is deduced by the compiler.
	Player(Cell grid[][Grid::height]);
};
#pragma once

#include <map>

#include "Cell.h"
#include "Game.h"
#include "Grid.h"


class Player
{
private:

	Cell cell;

	// dictionary of cells the player can move to
	std::map<Vector, Cell> movements;

	// helper function used in getMovements
	Cell getFurthestReachableCellInDirection(Vector vector, std::vector<std::vector<Cell>>);

	// check that we can move in the specified direction
	void getMovements(std::vector<std::vector<Cell>>);

public:

	// guess what
	void move(Vector vector, std::vector<std::vector<Cell>>);

	bool atfinish() { return this->cell.isfinish(); }

	// representation of a 2d array in a function param list, dont need to specify the length the first dimension, as it is deduced by the compiler.
	Player(std::vector<std::vector<Cell>>);
};
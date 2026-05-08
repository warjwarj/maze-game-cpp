#pragma once

#include <map>

#include "Cell.h"
#include "Game.h"
#include "Grid.h"
#include "Utils.h"

class Player
{
private:

	Cell* cell;
	std::map<Vector, Cell*> movements;
	Cell* getFurthestReachableCellInDirection(Vector vector, std::vector<std::vector<Cell*>>);
	void getMovements(std::vector<std::vector<Cell*>>);

public:

	void move(Vector vector, std::vector<std::vector<Cell*>>);
	bool atfinish() { return cell->isfinish(); }
	Player(std::vector<std::vector<Cell*>>);
};
#pragma once

#include <vector>
#include "Cell.h"

class Grid
{
	friend class Player;

private:

	int width;
	int height;
	void create();
	void maze();
	const Game& game;

public:

	std::vector<std::vector<Cell*>> grid;
	Grid(const Game& game);
};

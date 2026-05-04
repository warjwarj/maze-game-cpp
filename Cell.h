#pragma once

#include "Game.h"

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


public:

	Cell(int x, int y, SDL_Colour colour);
	Cell() = default;

	void draw(SDL_Colour colour);

	bool iswall() { return this->wall; }

	bool isfinish() { return this->finish; }

	int x;
	int y;
};
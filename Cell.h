#pragma once

#include "Game.h"

class Cell
{
	friend class Grid;

private:

	int cellSize;
	bool wall = false;
	bool visited = false;
	bool finish = false;
	SDL_Rect rect;
	const Game& game;

public:

	Cell(const Game& game, int x, int y, SDL_Colour colour);
	SDL_Colour colour;
	void draw();
	bool iswall() { return this->wall; }
	bool isfinish() { return this->finish; }
	int x;
	int y;
};
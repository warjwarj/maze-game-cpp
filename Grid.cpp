#include <iostream>
#include <stack>
#include <vector>
#include <cstdlib>
#include <random>
#include <functional>

#include "Grid.h"
#include "Game.h"
#include "Cell.h"
#include "Utils.h"

Grid::Grid(const Game& game) :
	game(game),
	width(game.gridWidth),
	height(game.gridHeight)
{
	create();
	maze();
}


void Grid::create()
{
	bool solid = false;
	for (int x=0; x < width; x++)
	{
		bool wall = false;
		grid.emplace_back();
		for (int y=0; y < height; y++)
		{
			grid[x].push_back(new Cell(game, x, y, WHITE));
			Cell* cell = grid[x][y];
			if (y == 0 || y == width - 1)
			{
				cell->colour = RED;
				cell->visited = true;
				cell->wall = true;
			}
			else
			{
				if (solid || wall)
				{
					cell->colour = BLACK;
					cell->wall = true;
				}
				if (x == 0 || x == width - 1)
				{
					cell->colour = RED;
					cell->visited = true;
					cell->wall = true;
				}
			}
			if (x == width - 3 && y == height - 3)
			{
				cell->colour = GREEN;
				cell->finish = true;
			}
			cell->draw();
			wall = !wall;
		}
		solid = !solid;
	}
}

// recursive backtracking
void Grid::maze()
{
	srand(time(NULL));

	// random start for the maze creation algorithm
	std::stack<Cell*> cell_stack;
	cell_stack.push(this->grid[rand() % (width / 2 - 1) * 2 + 2][rand() % (height / 2 - 1) * 2 + 2]);

	std::vector<Cell*> possible_paths;
	std::vector<Cell*> possible_walls;

	bool drawing_maze = true;

	int x;
	int y;
	int r;

	// recursive backtracker
	while (drawing_maze)
	{
		x = cell_stack.top()->x;
		y = cell_stack.top()->y;

		possible_paths.clear();
		possible_walls.clear();

		int asd = sizeof(this->grid);		

		// check index is in bounds
		if (x + 2 < this->grid.size())
			if (!this->grid[x + 2][y]->visited) {
				possible_paths.push_back(this->grid[x + 2][y]);
				possible_walls.push_back(this->grid[x + 1][y]);
			}
		if (x - 2 > 0)
			if (!this->grid[x - 2][y]->visited) {
				possible_paths.push_back(this->grid[x - 2][y]);
				possible_walls.push_back(this->grid[x - 1][y]);
			}
		if (y + 2 < this->grid.size())
			if (!this->grid[x][y + 2]->visited) {
				possible_paths.push_back(this->grid[x][y + 2]);
				possible_walls.push_back(this->grid[x][y + 1]);
			}
		if (y - 2 > 0)
			if (!this->grid[x][y - 2]->visited) {
				possible_paths.push_back(this->grid[x][y - 2]);
				possible_walls.push_back(this->grid[x][y - 1]);
			}
		cell_stack.top()->visited = true;

		// continue down branch
		if (!possible_paths.empty())
		{
			// random index in possible_paths
			r = rand() % possible_paths.size();

			// random cell to jump to next
			cell_stack.push(possible_paths[r]);

			// make the cell white and turn it into a path
			possible_walls[r]->colour = WHITE;
			possible_walls[r]->wall = false;
			possible_walls[r]->draw();
			continue;
		}
		else
		{
			// backtrack to last diversion
			cell_stack.pop();
			if (cell_stack.empty())
				drawing_maze = false;
		}
		SDL_RenderPresent(game.gameRenderer);
	}
}

void Grid::redrawCells()
{
	for (auto row : grid)
		for (Cell* c : row)
			c->draw();
}
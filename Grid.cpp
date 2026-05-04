
#include <iostream>
#include <stack>
#include <vector>
#include <cstdlib>
#include <random>
#include <functional>

#include "Grid.h"
#include "Game.h"
#include "Cell.h"

// Grid constructor
void Grid::create()
{
	bool solid = false;
	for (int x = 0; x < width; x++)
	{
		bool wall = false;
		grid.emplace_back();
		for (int y = 0; y < height; y++)
		{
			grid[x].emplace_back(x, y, WHITE);
			Cell& cell = grid[x][y];
			if (y == 0 || y == width - 1)
			{
				cell.draw(RED);
				cell.visited = true;
				cell.wall = true;
			}
			else
			{
				if (solid || wall)
				{
					cell.draw(BLACK);
					cell.wall = true;
				}
				if (x == 0 || x == width - 1)
				{
					cell.draw(RED);
					cell.visited = true;
					cell.wall = true;
				}
			}
			if (x == width - 3 && y == height - 3)
			{
				cell.finish = true;
				cell.draw(GREEN);
			}
			wall = !wall;
		}
		solid = !solid;
	}
}

// recursive backtracking
void Grid::maze()
{
	// get different number every time
	srand(time(NULL));

	// init cell_stack with a random cell from the grid
	std::stack<Cell*> cell_stack;
	cell_stack.push(&this->grid[rand() % (width / 2 - 1) * 2 + 2][rand() % (height / 2 - 1) * 2 + 2]);

	// white cells we can jump to, and the black walls inbetween.
	std::vector<std::reference_wrapper<Cell>> possible_paths;
	std::vector<std::reference_wrapper<Cell>> possible_walls;

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

		// check index is in bounds
		if (x + 2 < sizeof(this->grid)) {
			if (!this->grid[x + 2][y].visited) {
				possible_paths.push_back(this->grid[x + 2][y]);
				possible_walls.push_back(this->grid[x + 1][y]);
			}
		}
		if (x - 2 > 0) {
			if (!this->grid[x - 2][y].visited) {
				possible_paths.push_back(this->grid[x - 2][y]);
				possible_walls.push_back(this->grid[x - 1][y]);
			}
		}
		if (y + 2 < sizeof(this->grid)) {
			if (!this->grid[x][y + 2].visited) {
				possible_paths.push_back(this->grid[x][y + 2]);
				possible_walls.push_back(this->grid[x][y + 1]);
			}
		}
		if (y - 2 > 0) {
			if (!this->grid[x][y - 2].visited) {
				possible_paths.push_back(this->grid[x][y - 2]);
				possible_walls.push_back(this->grid[x][y - 1]);
			}
		}

		cell_stack.top()->visited = true;

		// continue down branch
		if (!possible_paths.empty())
		{
			// random index in possible_paths
			r = rand() % possible_paths.size();

			// random cell to jump to next
			cell_stack.push(&possible_paths[r].get());

			// make the cell white and turn it into a path
			possible_walls[r].get().draw(WHITE);
			possible_walls[r].get().wall = false;

			continue;
		}
		// backtrack to last diversion
		else
		{
			cell_stack.pop();

			if (cell_stack.empty())
			{
				drawing_maze = false;
			}
		}
		SDL_RenderPresent(Game::gameRenderer);
	}
}
#include <iostream>
#include <stack>
#include <vector>
#include <cstdlib>

#include <SDL.h>

#include "Structure.h"
#include "Game.h"

SDL_Color BLACK = { 0, 0, 0 ,255 };
SDL_Color WHITE = { 255, 255, 255 ,255 };
SDL_Color RED = { 222, 90, 67 ,255 };
SDL_Color DARK_BLUE = { 15, 99, 255 ,255 };
SDL_Color GREY = { 92, 92, 92 ,255 };
SDL_Color LIGHTER_GREY = { 145, 145, 145 ,255 };
SDL_Color GREEN = { 145, 145, 145 ,255 };


// Cell constructor
Cell::Cell(int x, int y, SDL_Colour colour) :
	y(y),
	x(x),
	colour(colour)
{
	this->rect.x = x * cell_size;
	this->rect.y = y * cell_size;
	this->rect.w = cell_size;
	this->rect.h = cell_size;

	this->draw(colour);
};


void Cell::draw(SDL_Colour colour)
{
	SDL_SetRenderDrawColor(Game::gameRenderer, colour.r, colour.g, colour.b, colour.a);
	SDL_RenderFillRect(Game::gameRenderer, &this->rect);
	SDL_RenderDrawRect(Game::gameRenderer, &this->rect);
};
	
// Grid constructor
void Grid::create()
{
	// FLAG - for a solid black (wall) column.
	bool solid = false;

	// WIDTH - each iteration is one column
	for (int x = 0; x < width; x++)
	{
		// FLAG - for a black (wall) cell
		bool wall = false;

		// HEIGHT - each iteration is one cell in a column
		for (int y = 0; y < height; y++)
		{
			Cell cell(x, y, WHITE);

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

			SDL_RenderPresent(Game::gameRenderer);

			wall = !wall;

			grid[x][y] = cell;
		}
		solid = !solid;
	}
}

// recursive backtracking
void Grid::maze()
{
	// .push() | .pop() | .empty() | .top()
	std::stack<Cell> cell_stack;

	// init cell_stack with a random cell from the grid
	cell_stack.push(this->grid[rand() % (width / 2 - 1) * 2 + 2][rand() % (height / 2 - 1) * 2 + 2]);

	bool drawing_maze = true;

	// recursively backtrack
	while (drawing_maze)
	{
		Cell startcell = cell_stack.top();

		int x = startcell.x;
		int y = startcell.y;

		// white cells we can jump to, and the black walls inbetween.
		std::vector<Cell> possible_paths;
		std::vector<Cell> possible_walls;

		if (!&this->grid[x + 2][y].wall && !&this->grid[x + 2][y].visited)
		{
			Cell& cell = this->grid[x + 2][y];
		}
		if (!&this->grid[x - 2][y].wall && !&this->grid[x - 2][y].visited)
		{
			Cell& cell = this->grid[x - 2][y];
		}
		if (!&this->grid[x][y + 2].wall && !&this->grid[x][y + 2].visited)
		{
			Cell& cell = this->grid[x][y + 2];
		}
		if (!&this->grid[x][y - 2].wall && !&this->grid[x - 2][y].visited)
		{
			Cell& cell = this->grid[x][y - 2];
		}
		
	}
}
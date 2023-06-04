#include <iostream>
#include <stack>
#include <vector>
#include <cstdlib>
#include <random>

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

	srand(time(NULL));

	// init cell_stack with a random cell from the grid
	cell_stack.push(this->grid[rand() % (width / 2 - 1) * 2 + 2][rand() % (height / 2 - 1) * 2 + 2]);

	bool drawing_maze = true;

	// recursively backtrack
	while (drawing_maze)
	{
		Cell& startcell = cell_stack.top();

		std::cout << "startcell visisted before path selection: " << startcell.visited << std::endl;

		int x = startcell.x;
		int y = startcell.y;

		// white cells we can jump to, and the black walls inbetween.
		std::vector<Cell> possible_paths;
		std::vector<Cell> possible_walls;

		if (x + 2 < sizeof(&this->grid)) {
			Cell &path = this->grid[x + 2][y];
			Cell &wall = this->grid[x + 1][y];
			if (!path.visited) {
				std::cout << "path visited: " << path.visited << std::endl;
				possible_paths.push_back(path);
				possible_walls.push_back(wall);
			}
		}
		if (x - 2 > 0) {
			Cell &path = this->grid[x - 2][y];
			Cell &wall = this->grid[x - 1][y];
			if (!path.visited) {
				std::cout << "path visited: " << path.visited << std::endl;
				possible_paths.push_back(path);
				possible_walls.push_back(wall);
			}
		}
		if (y + 2 < sizeof(&this->grid)) {
			Cell &path = this->grid[x][y + 2];
			Cell &wall = this->grid[x][y + 1];
			if (!path.visited) {
				std::cout << "path visited: " << path.visited << std::endl;
				possible_paths.push_back(path);
				possible_walls.push_back(wall);
			}
		}
		if (y - 2 > 0) {
			Cell &path = this->grid[x][y - 2];
			Cell &wall = this->grid[x][y - 1];
			if (!path.visited) {
				std::cout << "path visited: " << path.visited << std::endl;
				possible_paths.push_back(path);
				possible_walls.push_back(wall);
			}
		}

		// continue down branch
		if (!possible_paths.empty())
		{
			//std::cout << "possible_paths is not empty." << " " << possible_paths.size() << std::endl;

			std::random_device rd; // obtain a random number from hardware
			std::mt19937 gen(rd()); // seed the generator
			std::uniform_int_distribution<> distr(0, possible_paths.size() - 1); // define the range

			int r = distr(gen);

			Cell& path = possible_paths[r];
			Cell& wall = possible_walls[r];

			// random cell to jump to next
			cell_stack.push(path);

			wall.draw(WHITE);
			wall.wall = false;

			startcell.visited = true;
			std::cout << "startcell visited after path selction: " << startcell.visited << std::endl;
		}
		// backtrack to last diversion
		else
		{
			//std::cout << "possible_paths is empty." << std::endl;

			cell_stack.pop();

			if (cell_stack.empty())
			{
				drawing_maze = false;
			}
		}
		SDL_RenderPresent(Game::gameRenderer);
	}
}
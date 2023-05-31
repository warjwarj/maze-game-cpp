#include <vector>

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
	SDL_SetRenderDrawColor(Game::gameRenderer, 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(Game::gameRenderer, &this->rect);
};

// Grid constructor
Grid::Grid()
{
	// FLAG - for a solid black (wall) column.
	bool solid = true;

	// WIDTH - each iteration is one column
	for (int x = 0; x < this->width; x++)
	{
		// FLAG - for a black (wall) cell
		bool wall = false;

		// HEIGHT - each iteration is one cell in a column
		for (int y = 0; y < this->height; y++)
		{
			// instantiate the cell
			Cell cell(x, y, WHITE);

			if (y == 0 || y == this->width - 1 || x == 0 || x == this->width - 1)
			{
				cell.draw(RED);
				cell.visited = true;
				cell.wall = true;
			}
			else if (solid == true || wall == true)
			{
				cell.draw(BLACK);
				cell.wall = true;
			}
			wall = !wall;
			grid[x][y] = cell;
		}
		solid = !solid;
	}
}
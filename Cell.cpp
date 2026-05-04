
#include "Cell.h"
#include "Game.h"

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
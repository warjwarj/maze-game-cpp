#include "Cell.h"
#include "Game.h"

// Cell constructor
Cell::Cell(const Game& game, int x, int y, SDL_Colour colour) :
	game(game),
	y(y),
	x(x),
	colour(colour),
	cellSize(game.cellSize)
{
	const int adjustedWidthStart = game.getScreenWidth() - game.getinnerWindowPositionX();
	const int adjustedHeightStart = game.getScreenHeight() - game.getinnerWindowPositionY();

	this->rect.x = adjustedWidthStart + (x * cellSize);
	this->rect.y = adjustedHeightStart + (y * cellSize);
	this->rect.w = cellSize;
	this->rect.h = cellSize;

	this->draw(colour);
};


void Cell::draw(SDL_Colour colour)
{
	SDL_SetRenderDrawColor(this->game.gameRenderer, colour.r, colour.g, colour.b, colour.a);
	SDL_RenderFillRect(this->game.gameRenderer, &this->rect);
	SDL_RenderDrawRect(this->game.gameRenderer, &this->rect);
};
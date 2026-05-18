
#include "Clickable.h"
#include "Game.h"

Clickable::Clickable(const Game& game, SDL_Colour colour, std::string text, int x, int y, int w, int h, bool centered) :
	game(game),
	colour(colour),
	text(text)
{
	rect.x = centered ? x - (w / 2) : x;
	rect.y = centered ? y - (h / 2) : y;
	rect.w = w;
	rect.h = h;

	SDL_SetRenderDrawColor(game.gameRenderer, colour.r, colour.g, colour.b, colour.a);
	SDL_RenderFillRect(game.gameRenderer, &rect);
	SDL_RenderDrawRect(game.gameRenderer, &rect);

	game.renderText(text, x, y, centered);
}

bool Clickable::contains(int clickX, int clickY) const
{
	return clickX >= rect.x && clickX <= rect.x + rect.w &&
		clickY >= rect.y && clickY <= rect.y + rect.h;
}
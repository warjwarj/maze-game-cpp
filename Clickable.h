#pragma once

#include <string>
#include <functional>

#include <SDL.h>

class Game;

class Clickable 
{
private:
	SDL_Rect rect;
	std::string text;
	SDL_Colour colour;
	const Game& game;
public:
	std::function<void()> onClick;
	Clickable(const Game& game, SDL_Colour colour, std::string text, int x, int y, int w, int h, bool centered);
	bool contains(int clickX, int clickY) const;
};
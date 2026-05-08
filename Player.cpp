
#include <iostream>

#include "Cell.h"
#include "Grid.h"
#include "Player.h"
#include "Utils.h"


Player::Player(std::vector<std::vector<Cell*>> grid) :
	cell(grid[2][2])
{
	move(none, grid);
}

void Player::move(Vector vector, std::vector<std::vector<Cell*>> grid)
{
	// remove old movement hint squares and also blue square
	for (auto& i : movements)
		std::get<1>(i)->draw(WHITE);
	cell->draw(WHITE);

	// make chosen movement the current cell
	if (vector != none)
		if (movements.count(vector) != 0)
			cell = movements.at(vector);
		else
			std::cout << "you cannot move in that direction" << std::endl;

	// redraw and get new cell's possible movements
	getMovements(grid);
	cell->draw(DARK_BLUE);
}

Cell* Player::getFurthestReachableCellInDirection(Vector vector, std::vector<std::vector<Cell*>> grid)
{
	int x = cell->x;
	int y = cell->y;

	bool reached_wall = false;
	int distance = 0;

	while (!reached_wall)
	{
		switch (vector)
		{
		case up_max:
			if (!grid[x][y - distance]->iswall())
			{
				distance++;
				break;
			}
			else
			{
				distance--;
				grid[x][y - distance]->draw(LIGHTER_GREY);
				return grid[x][y - distance];
			}
		case down_max:
			if (!grid[x][y + distance]->iswall())
			{
				distance++;
				break;
			}
			else
			{
				distance--;
				grid[x][y + distance]->draw(LIGHTER_GREY);
				return grid[x][y + distance];
			}
		case left_max:
			if (!grid[x - distance][y]->iswall())
			{
				distance++;
				break;
			}
			else
			{
				distance--;
				grid[x - distance][y]->draw(LIGHTER_GREY);
				return grid[x - distance][y];
			}
		case right_max:
			if (!grid[x + distance][y]->iswall())
			{
				distance++;
				break;
			}
			else
			{
				distance--;
				grid[x + distance][y]->draw(LIGHTER_GREY);
				return grid[x + distance][y];
			}
		}
	}
}

void Player::getMovements(std::vector<std::vector<Cell*>> grid)
{
	this->movements.clear();

	int x = cell->x;
	int y = cell->y;

	// up
	if (!grid[x][y - 1]->iswall())
	{
		this->movements.insert({ up_one, grid[x][y - 1] });
		this->movements.insert({ up_max, this->getFurthestReachableCellInDirection(up_max, grid) });
	}
	// down
	if (!grid[x][y + 1]->iswall())
	{
		this->movements.insert({ down_one, grid[x][y + 1] });
		this->movements.insert({ down_max, this->getFurthestReachableCellInDirection(down_max, grid) });
	}
	// left
	if (!grid[x - 1][y]->iswall())
	{
		this->movements.insert({ left_one, grid[x - 1][y] });
		this->movements.insert({ left_max, this->getFurthestReachableCellInDirection(left_max, grid) });
	}
	// right
	if (!grid[x + 1][y]->iswall())
	{
		this->movements.insert({ right_one, grid[x + 1][y] });
		this->movements.insert({ right_max, this->getFurthestReachableCellInDirection(right_max, grid) });
	}
}
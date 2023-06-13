
#include <iostream>

#include "Movement.h"
#include "Game.h";

Player::Player(Cell(*grid)[Grid::width][Grid::height])
{
	for (int i=0; i < Grid::width; i++)
	{
		for (int j=0; j < Grid::height; j++)
		{
			std::cout << grid[i][j]->x << " " << grid[i][j]->y << std::endl;
		}
	}

	this->cell = *grid[2][2];
	this->cell.draw(GREEN);
}

Cell Player::getFurthestCellInDirection(Vector vector, Cell** grid, Cell cell)
{
	int x = cell.x;
	int y = cell.y;

	bool reached_wall = false;
	int distance = 0;

	while (!reached_wall)
	{
		switch (vector)
		{
		case up_max:
			if (!grid[x][y - distance].iswall())
			{
				distance++;
				break;
			}
			else
			{
				grid[x][y - distance].draw(LIGHTER_GREY);
				return grid[x][y - distance];
			}
		case down_max:
			if (!grid[x][y + distance].iswall())
			{
				distance++;
				break;
			}
			else
			{
				grid[x][y - distance].draw(LIGHTER_GREY);
				return grid[x][y - distance];
			}
		case left_max:
			if (!grid[x - distance][y].iswall())
			{
				distance++;
				break;
			}
			else
			{
				grid[x][y - distance].draw(LIGHTER_GREY);
				return grid[x][y - distance];
			}
		case right_max:
			if (!grid[x + distance][y].iswall())
			{
				distance++;
				break;
			}
			else
			{
				grid[x][y - distance];
				return grid[x][y - distance];
			}
		}
	}
}

void Player::getMovements(Vector vector, Cell** grid)
{
	int x = this->cell.x;
	int y = this->cell.y;

	// up
	if (!grid[x][y - 1].iswall())
	{
		this->movements.insert({ up_one, grid[x][y - 1] });
		this->movements.insert({ up_max, this->getFurthestCellInDirection(up_max, grid, this->cell) });
	}
	// down
	if (!grid[x][y + 1].iswall())
	{
		this->movements.insert({ down_one, grid[x][y + 1] });
		this->movements.insert({ down_max, this->getFurthestCellInDirection(down_max, grid, this->cell) });
	}
	// left
	if (!grid[x - 1][y].iswall())
	{
		this->movements.insert({ left_one, grid[x - 1][y] });
		this->movements.insert({ left_max, this->getFurthestCellInDirection(left_max, grid, this->cell) });
	}
	// right
	if (!grid[x + 1][y].iswall())
	{
		this->movements.insert({ right_one, grid[x + 1][y] });
		this->movements.insert({ right_max, this->getFurthestCellInDirection(right_max, grid, this->cell) });
	}
}
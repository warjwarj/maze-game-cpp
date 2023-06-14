
#include <iostream>

#include "Movement.h"
#include "Game.h";

Player::Player(Cell grid[][Grid::height])
{
	//for (int i=0; i < Grid::width; i++)
	//{
	//	for (int j=0; j < Grid::height; j++)
	//	{
	//		std::cout << grid[i][j].x << " " << grid[i][j].y << std::endl;
	//	}
	//}

	this->cell = grid[2][2];
	this->move(none, grid);
}

void Player::move(Vector vector, Cell grid[][Grid::height])
{
	if (vector != none)
	{
		if (this->movements.count(vector) != 0)
		{
			this->cell = movements.at(vector);
		}
		else
		{
			std::cout << "you cannot move in that direction" << std::endl;
		}
	}
	this->cell.draw(DARK_BLUE);
	this->getMovements(grid);
}

Cell Player::getFurthestReachableCellInDirection(Vector vector, Cell grid[][Grid::height])
{
	int x = this->cell.x;
	int y = this->cell.y;

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
				distance--;
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
				distance--;
				grid[x][y + distance].draw(LIGHTER_GREY);
				return grid[x][y + distance];
			}
		case left_max:
			if (!grid[x - distance][y].iswall())
			{
				distance++;
				break;
			}
			else
			{
				distance--;
				grid[x - distance][y].draw(LIGHTER_GREY);
				return grid[x - distance][y];
			}
		case right_max:
			if (!grid[x + distance][y].iswall())
			{
				distance++;
				break;
			}
			else
			{
				distance--;
				grid[x + distance][y].draw(LIGHTER_GREY);
				return grid[x + distance][y];
			}
		}
	}
}

void Player::getMovements(Cell grid[][Grid::height])
{
	this->movements.clear();

	int x = this->cell.x;
	int y = this->cell.y;

	// up
	if (!grid[x][y - 1].iswall())
	{
		this->movements.insert({ up_one, grid[x][y - 1] });
		this->movements.insert({ up_max, this->getFurthestReachableCellInDirection(up_max, grid) });
	}
	// down
	if (!grid[x][y + 1].iswall())
	{
		this->movements.insert({ down_one, grid[x][y + 1] });
		this->movements.insert({ down_max, this->getFurthestReachableCellInDirection(down_max, grid) });
	}
	// left
	if (!grid[x - 1][y].iswall())
	{
		this->movements.insert({ left_one, grid[x - 1][y] });
		this->movements.insert({ left_max, this->getFurthestReachableCellInDirection(left_max, grid) });
	}
	// right
	if (!grid[x + 1][y].iswall())
	{
		this->movements.insert({ right_one, grid[x + 1][y] });
		this->movements.insert({ right_max, this->getFurthestReachableCellInDirection(right_max, grid) });
	}
}
#include "header.h"
#include "functions.h"

bool placeShips(int arrGraph[][BS], int rands[], int i, int j, int counter)
{
	int coords[8][2] = {
		{-1, 1},
		{0, 1},
		{1, 1},
		{1, 0},
		{1, -1},
		{0, -1},
		{-1, -1},
		{-1, 0}
	};

	srand(time(0)); // ?
	int direction = rands[counter];
	char dirResult = '-';

	switch (direction)
	{
	case 0:
	{
		int y = 0;

		for (y; y < ships[counter]; y++)
		{
			for (int U = 0; U < 8; U++)
			{
				for (int O = 0; O < 8; O++)
				{
					if (arrGraph[i + y + coords[U][0]][j + coords[O][1]] == 9)
					{
						return false;
					}
				}
			}
			if (arrGraph[i + y][j] != 10 || i + y >= 10)
			{
				break;
			}
		}
		if (arrGraph[i + y][j] != 10 || i + y >= 10)
		{
			break;
		}
		dirResult = 'd';
		break;
	}
	case 1:
	{
		int x = 0;

		for (x; x < ships[counter]; x++)
		{
			for (int U = 0; U < 8; U++)
			{
				for (int O = 0; O < 8; O++)
				{
					if (arrGraph[i + coords[U][0]][j + x + coords[O][1]] == 9)
					{
						return false;
					}
				}
			}
			if (arrGraph[i][j + x] != 10 || j + x >= 10)
			{
				break;
			}
		}
		if (arrGraph[i][j + x] != 10 || j + x >= 10)
		{
			break;
		}
		dirResult = 'r';
		break;
	}
	case 2:
	{
		int y = 0;

		for (y; y < ships[counter]; y++)
		{
			for (int U = 0; U < 8; U++)
			{
				for (int O = 0; O < 8; O++)
				{
					if (arrGraph[i - y + coords[U][0]][j + coords[O][1]] == 9)
					{
						return false;
					}
				}
			}
			if (arrGraph[i - y][j] != 10 || i - y < 0)
			{
				break;
			}
		}
		if (arrGraph[i - y][j] != 10 || i - y < 0)
		{
			break;
		}
		dirResult = 'u';
		break;
	}
	case 3:
	{
		int x = 0;

		for (x; x < ships[counter]; x++)
		{
			for (int U = 0; U < 8; U++)
			{
				for (int O = 0; O < 8; O++)
				{
					if (arrGraph[i + coords[U][0]][j - x + coords[O][1]] == 9)
					{
						return false;
					}
				}
			}
			if (arrGraph[i][j - x] != 10 || j - x < 0)
			{
				break;
			}
		}
		if (arrGraph[i][j - x] != 10 || j - x < 0)
		{
			break;
		}
		dirResult = 'l';
		break;
	}
	default:
		break;
	}



	switch (dirResult)
	{
	case 'd':
	{
		for (int y = 0; y < ships[counter]; y++)
		{
			arrGraph[i + y][j] = 9;

		}
		return true;
	}
	case 'r':
	{
		for (int x = 0; x < ships[counter]; x++)
		{
			arrGraph[i][j + x] = 9;
		}
		return true;
	}
	case 'u':
	{
		for (int y = 0; y < ships[counter]; y++)
		{
			arrGraph[i - y][j] = 9;
		}
		return true;
	}
	case 'l':
	{
		for (int x = 0; x < ships[counter]; x++)
		{
			arrGraph[i][j - x] = 9;
		}
		return true;
	}
	default:
		return false;
	}
}

void changeShipsPlacement(int arrGraph[][BS])
{
	makeCleanBoard(arrGraph);

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			arrGraph[i][j] = 99;
		}
	}

	int counter = 0;
	int rands[10];

	for (int i = 0; i < 10; i++)
	{
		rands[i] = rand() % 3;
	}

	srand(time(0));

	while (true)
	{
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (counter < 10 && rand() % 40 == 0 && arrGraph[i][j] != 9)
				{
					if (placeShips(arrGraph, rands, i, j, counter))
					{
						counter++;
					}
				}
				else if (arrGraph[i][j] != 9)
				{
					arrGraph[i][j] = 10;
				}
			}
		}

		if (counter >= 10)
		{
			break;
		}
	}
}

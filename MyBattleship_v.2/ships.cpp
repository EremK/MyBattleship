#include "header.h"
#include "functions.h"

bool placeShips(int arrGraph[][BS], int rands[], int i, int j, int counter)
{
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
	srand(time(0));

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

bool placeShips(int arrGraph[][BS], int rands[], int i, int j, int counter, int** shipCoords) // not completed
{
	std::cout << "1\n";

	srand(time(0)); // ?
	int direction = 0;
	char dirResult = '-';

	std::cout << "2\n";

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

	std::cout << "3\n";

	switch (dirResult)
	{
	case 'd':
	{
		for (int y = 0; y < ships[counter]; y++)
		{
			shipCoords[y][0] = i + y;
			shipCoords[y][1] = j;

			for (int g = 0; g < ships[counter]; g++) // t
			{
				std::cout << shipCoords[g][0] << "\t" << shipCoords[g][1] << std::endl;
			} // t

			std::cout << "SUCCESS@@@\n"; // t
			//std::cout << shipCoords << std::endl;
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

void mannualShipPlacement(int arrGraph[][BS], int counter, int** shipCoords)
{
	std::cout << "Start\n";
	bool shipNotExist = true;

	while (shipNotExist)
	{
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (rand() % 5 == 0 && arrGraph[i][j] != 9) // (counter < 10 && 
				{
					if (placeShips(arrGraph, 0, i, j, counter, shipCoords))
					{
						shipNotExist = false;
						break;
					}
				}
				else if (arrGraph[i][j] != 9)
				{
					arrGraph[i][j] = 10;
				}
			}
			if (!shipNotExist) break;
		}
	}

	std::cout << "PreNext\n";

	std::cout << shipCoords << std::endl;

	for (int g = 0; g < ships[counter]; g++) // t
	{
		std::cout << shipCoords[g][0] << "\t" << shipCoords[g][1] << std::endl;
	} // t

	std::cout << "Next\n";

	//int dx = 0, dy = 0;

	//while (app.pollEvent(e))
	//{
	//	if (e.type == Event::Closed)
	//		app.close();

	//	if (e.type == Event::KeyPressed)
	//	{
	//		if (e.key.code == Keyboard::Left)
	//		{
	//			std::cout << "L\n";
	//			dx = -1;
	//		}
	//		else if (e.key.code == Keyboard::Right)
	//		{
	//			std::cout << "R\n";
	//			dx = 1;
	//		}
	//		else if (e.key.code == Keyboard::Up)
	//		{
	//			std::cout << "U\n";
	//			dy = -1;
	//		}
	//		else if (e.key.code == Keyboard::Down)
	//		{
	//			std::cout << "D\n";
	//			dy = 1;
	//		}
	//		else if (e.key.code == Keyboard::Enter)
	//		{
	//			std::cout << "Enter\n";
	//			break;
	//		}

	//		for (int z = 0; z < ships[counter]; z++)
	//		{
	//			shipCoords[z][0] += dx;
	//			shipCoords[z][1] += dy;
	//			dx = 0, dy = 0;
	//		}
	//	}
	//	Sleep(100);
	//	std::cout << "Infinitive!\n";
	//}
}

bool mannualMoveCheck(int arrGraph[][BS], int counter, int** shipCoords, int dx, int dy, bool shipIsVertical)
{
	const int moveLeft[3][2] = {
		{-1, -1},
		{0, -1},
		{1, -1}
	};
	const int moveRight[3][2] = {
		{-1, 1},
		{0, 1},
		{1, 1}
	};
	const int moveUp[3][2] = {
		{-1, -1},
		{-1, 0},
		{-1, 1}
	};
	const int moveDown[3][2] = {
		{1, -1},
		{1, 0},
		{1, 1}
	};

	std::cout << "Entered manualMoveCheck() function!\n";

	if (dy == -1)
	{
		for (int y = 0; y < ships[counter]; y++)
		{
			int t_x = shipCoords[y][0] + dx;
			int t_y = shipCoords[y][1] + dy;
			if (t_x > 9 || t_x < 0 || t_y > 9 || t_y < 0)
				return false;
			std::cout << t_x << "\t" << t_y << std::endl;

			if (shipIsVertical)
			{
				for (int U = 0; U < 3; U++)
				{
					if (arrGraph[t_x + moveLeft[U][0]][t_y + moveLeft[U][1]] == 9)
					{
						std::cout << "return false;\n";
						std::cout << t_y + moveLeft[U][0] << std::endl;
						std::cout << t_x + moveLeft[U][1] << std::endl;
						return false;
					}
				}
			}
			else if (!shipIsVertical && y == 0)
			{
				for (int U = 0; U < 3; U++)
				{
					if (arrGraph[t_x + moveLeft[U][0]][t_y + moveLeft[U][1]] == 9)
					{
						std::cout << "return false;\n";
						std::cout << t_y + moveLeft[U][0] << std::endl;
						std::cout << t_x + moveLeft[U][1] << std::endl;
						return false;
					}
				}
			}

		}
		return true;
	}
	else if (dy == 1)
	{
		for (int y = 0; y < ships[counter]; y++)
		{
			int t_x = shipCoords[y][0] + dx;
			int t_y = shipCoords[y][1] + dy;
			if (t_x > 9 || t_x < 0 || t_y > 9 || t_y < 0)
				return false;
			std::cout << t_x << "\t" << t_y << std::endl; // 


			if (shipIsVertical)
			{
				for (int U = 0; U < 3; U++)
				{
					if (arrGraph[t_x + moveRight[U][0]][t_y + moveRight[U][1]] == 9)
					{
						return false;
					}
				}
			}
			else if (!shipIsVertical && y == ships[counter] - 1)
			{
				for (int U = 0; U < 3; U++)
				{
					if (arrGraph[t_x + moveRight[U][0]][t_y + moveRight[U][1]] == 9)
					{
						return false;
					}
				}
			}
		}
		return true;
	}
	else if (dx == -1)
	{
		for (int y = 0; y < ships[counter]; y++)
		{
			int t_x = shipCoords[y][0] + dx;
			int t_y = shipCoords[y][1] + dy;
			if (t_x > 9 || t_x < 0 || t_y > 9 || t_y < 0)
				return false;
			std::cout << t_x << "\t" << t_y << std::endl;

			if (shipIsVertical && y == 0)
			{
				for (int U = 0; U < 3; U++)
				{
					if (arrGraph[t_x + moveUp[U][0]][t_y + moveUp[U][1]] == 9)
					{
						return false;
					}
				}
			}
			else if (!shipIsVertical)
			{
				for (int U = 0; U < 3; U++)
				{
					if (arrGraph[t_x + moveUp[U][0]][t_y + moveUp[U][1]] == 9)
					{
						return false;
					}
				}
			}
		}
		return true;
	}
	else if (dx == 1)
	{
		for (int y = 0; y < ships[counter]; y++)
		{
			int t_x = shipCoords[y][0] + dx;
			int t_y = shipCoords[y][1] + dy;
			if (t_x > 9 || t_x < 0 || t_y > 9 || t_y < 0)
				return false;
			std::cout << t_x << "\t" << t_y << std::endl;

			if (shipIsVertical && y == ships[counter] - 1)
			{
				for (int U = 0; U < 3; U++)
				{
					if (arrGraph[t_x + moveDown[U][0]][t_y + moveDown[U][1]] == 9)
					{
						return false;
					}
				}
			}
			else if (!shipIsVertical)
			{
				for (int U = 0; U < 3; U++)
				{
					if (arrGraph[t_x + moveDown[U][0]][t_y + moveDown[U][1]] == 9)
					{
						return false;
					}
				}
			}
		}
		return true;
	}
	else
	{
		return false;
	}
}

bool turnShip(int arrGraph[][BS], int counter, int** shipCoords, bool shipIsVertical) 
{
	bool turnIsNotCorrect = false;

	if (shipIsVertical)
	{
		for (int i = 1; i < ships[counter]; i++)
		{
			if (arrGraph[shipCoords[0][0]][shipCoords[0][1] + i] != 10 || shipCoords[0][1] + i > 9)
			{
				turnIsNotCorrect = true;
			}

			if (i == ships[counter] - 1) 
			{
				for (int O = 0; O < 8; O++)
				{
					if (arrGraph[shipCoords[0][0] + coords[O][0]][shipCoords[0][1] + i + coords[O][1]] == 9) 
					{
						if (O == 5) continue;
						turnIsNotCorrect = true;
					}
				}
			}
		}

		if (!turnIsNotCorrect)
		{
			for (int i = 1; i < ships[counter]; i++)
			{
				arrGraph[shipCoords[i][0]][shipCoords[i][1]] = 10;
				arrGraph[shipCoords[0][0]][shipCoords[0][1] + i] = 9;
				shipCoords[i][0] = shipCoords[0][0];
				shipCoords[i][1] = shipCoords[0][1] + i;
			}
			return false;
		}
	}
	else
	{
		for (int i = 1; i < ships[counter]; i++)
		{
			if (arrGraph[shipCoords[0][0] + i][shipCoords[0][1]] != 10 || shipCoords[0][0] + i > 9)
			{
				turnIsNotCorrect = true;
			}

			if (i == ships[counter] - 1)
			{
				for (int O = 0; O < 8; O++)
				{
					if (arrGraph[shipCoords[0][0] + i + coords[O][0]][shipCoords[0][1] + coords[O][1]] == 9) // <-|
					{
						if (O == 7) continue;
						turnIsNotCorrect = true;
					}
				}
			}
		}

		if (!turnIsNotCorrect)
		{
			for (int i = 1; i < ships[counter]; i++)
			{
				arrGraph[shipCoords[i][0]][shipCoords[i][1]] = 10;
				arrGraph[shipCoords[0][0] + i][shipCoords[0][1]] = 9;
				shipCoords[i][0] = shipCoords[0][0] + i;
				shipCoords[i][1] = shipCoords[0][1];
			}
			return true;
		}
	}
	return shipIsVertical;
}
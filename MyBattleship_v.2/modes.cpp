#include "header.h"
#include "functions.h"

void playersMove(int myShotBoard[][BS], int urGameGraph[][BS], int x, int y)
{
	if (urGameGraph[x][y] == 10) // Нет пробития
	{
		myShotBoard[x][y] = 0;
		urGameGraph[x][y] = 0; // Пустая клетка
	}
	else if (urGameGraph[x][y] == 9) // Есть пробитие
	{
		myShotBoard[x][y] = 5;
		urGameGraph[x][y] = 5; // Клетка битого корабля
	}
}

void smartBotMove(int urShotBoard[][BS], int myGameGraph[][BS], bool& opositeDirCheck, int& x, int& y, bool& hit, char& dir)
{
	if (dir == '-')
	{
		if (urShotBoard[x + 1][y] == 10 && x + 1 < 10)
		{
			playersMove(urShotBoard, myGameGraph, x + 1, y);
			if (urShotBoard[x + 1][y] == 5)
			{
				dir = 'd';
				++x;
			}
		}
		else if (urShotBoard[x][y + 1] == 10 && y + 1 < 10)
		{
			playersMove(urShotBoard, myGameGraph, x, y + 1);
			if (urShotBoard[x][y + 1] == 5)
			{
				dir = 'r';
				++y;
			}
		}
		else if (urShotBoard[x - 1][y] == 10 && x - 1 > 0)
		{
			playersMove(urShotBoard, myGameGraph, x - 1, y);
			if (urShotBoard[x - 1][y] == 5)
			{
				dir = 'u';
				--x;
			}
		}
		else if (urShotBoard[x][y - 1] == 10 && y - 1 > 0)
		{
			playersMove(urShotBoard, myGameGraph, x, y - 1);
			if (urShotBoard[x][y - 1] == 5)
			{
				dir = 'l';
				y--;
			}
		}
		else
		{
			dir = '-';
			hit = false;
			opositeDirCheck = false;

			randomShot(urShotBoard, myGameGraph, x, y);
			return;
		}
	}
	// -----
	else if (opositeDirCheck)
	{
		bool makeRandShot = false;

		switch (dir)
		{
		case 'd':
		{
			while (true)
			{
				--x;
				if (x < 0 || urShotBoard[x][y] == 0)
				{
					dir = '-';
					hit = false;
					opositeDirCheck = false;
					makeRandShot = true;
					break;
				}

				if (urShotBoard[x][y] == 10)
				{
					playersMove(urShotBoard, myGameGraph, x, y);
					if (urShotBoard[x][y] == 0)
					{
						dir = '-';
						hit = false;
						opositeDirCheck = false;
						break;
					}
				}
				else
					continue;
			}
			break;
		}
		case 'r':
		{
			while (true)
			{
				--y;
				if (y < 0 || urShotBoard[x][y] == 0)
				{
					dir = '-';
					hit = false;
					opositeDirCheck = false;
					makeRandShot = true;
					break;
				}

				if (urShotBoard[x][y] == 10)
				{
					playersMove(urShotBoard, myGameGraph, x, y);

					dir = '-';
					hit = false;
					opositeDirCheck = false;
					break;

				}
				else
					continue;
			}
			break;
		}
		case 'u':
		{
			while (true)
			{
				++x;
				if (x > 10 || urShotBoard[x][y] == 0)
				{
					dir = '-';
					hit = false;
					opositeDirCheck = false;
					makeRandShot = true;
					break;
				}

				if (urShotBoard[x][y] == 10)
				{
					playersMove(urShotBoard, myGameGraph, x, y);

					dir = '-';
					hit = false;
					opositeDirCheck = false;
					break;

				}
				else
					continue;
			}
			break;
		}
		case 'l':
		{
			while (true)
			{
				++y;
				if (y > 10 || urShotBoard[x][y] == 0)
				{
					dir = '-';
					hit = false;
					opositeDirCheck = false;
					makeRandShot = true;
					break;
				}

				if (urShotBoard[x][y] == 10)
				{
					playersMove(urShotBoard, myGameGraph, x, y);

					dir = '-';
					hit = false;
					opositeDirCheck = false;
					break;

				}
				else
					continue;
			}
			break;
		}
		}
		if (makeRandShot) //
		{
			randomShot(urShotBoard, myGameGraph, x, y);
			dir = '-';
			hit = false;
			opositeDirCheck = false;
			return;
		}
	} // -----
	else
	{
		switch (dir)
		{
		case 'd':
		{
			if (urShotBoard[x + 1][y] == 10 && x < 10)
			{

				playersMove(urShotBoard, myGameGraph, ++x, y);

				if (urShotBoard[x][y] == 0 || urShotBoard[x + 1][y] == 0)
				{
					opositeDirCheck = true;
					break;
				}
			}
			else
			{
				dir = '-';
				hit = false;
				opositeDirCheck = false;

				randomShot(urShotBoard, myGameGraph, x, y);
				return;
			}
			break;
		}
		case 'r':
		{
			if (urShotBoard[x][y + 1] == 10 && y < 10)
			{
				playersMove(urShotBoard, myGameGraph, x, ++y);

				if (urShotBoard[x][y] == 0 || urShotBoard[x][y + 1] == 0)
				{
					opositeDirCheck = true;
					break;
				}
			}
			else
			{
				dir = '-';
				hit = false;
				opositeDirCheck = false;

				randomShot(urShotBoard, myGameGraph, x, y);
				return;
			}
			break;
		}
		case 'u':
		{
			if (urShotBoard[x - 1][y] == 10 && x > 0)
			{
				playersMove(urShotBoard, myGameGraph, --x, y);

				if (urShotBoard[x][y] == 0 || urShotBoard[x - 1][y] == 0)
				{
					opositeDirCheck = true;
					break;
				}
			}
			else
			{
				dir = '-';
				hit = false;
				opositeDirCheck = false;

				randomShot(urShotBoard, myGameGraph, x, y);
				return;
			}
			break;
		}
		case 'l':
		{
			if (urShotBoard[x][y - 1] == 10 && y > 0)
			{
				playersMove(urShotBoard, myGameGraph, x, --y);

				if (urShotBoard[x][y] == 0 || urShotBoard[x][y - 1] == 0)
				{
					//opositeDirCheck = true;
					dir = '-';
					hit = false;
					opositeDirCheck = false;
					break;
				}
			}
			else
			{
				dir = '-';
				hit = false;
				opositeDirCheck = false;

				randomShot(urShotBoard, myGameGraph, x, y);
				return;
			}
			break;
		}
		}
	}
}

void randomShot(int urShotBoard[][BS], int myGameGraph[][BS], int& x, int& y)
{
	while (1)
	{
		x = rand() % 10;
		y = rand() % 10;

		if (urShotBoard[y][x] == 0 || urShotBoard[y][x] == 5)
			continue;
		break;
	}

	playersMove(urShotBoard, myGameGraph, y, x);
}

//void smartBotLogic()
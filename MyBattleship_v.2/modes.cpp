#include "header.h"
#include "functions.h"

void playersMove(int myShotBoard[][BS], int urGameGraph[][BS], int x, int y)
{
	if (urGameGraph[x][y] == 10) // ��� ��������
	{
		myShotBoard[x][y] = 0;
		urGameGraph[x][y] = 0; // ������ ������
	}
	else if (urGameGraph[x][y] == 9) // ���� ��������
	{
		myShotBoard[x][y] = 5;
		urGameGraph[x][y] = 5; // ������ ������ �������
	}
}

void smartBotMove(int urShotBoard[][BS], int myGameGraph[][BS], int& x, int& y, bool& hit, char& dir)
{
	if (dir == '-')
	{
		if (urShotBoard[x + 1][y] == 10)
		{
			playersMove(urShotBoard, myGameGraph, ++x, y);
			dir = 'd';
		}
		else if (urShotBoard[x][y + 1] == 10)
		{
			playersMove(urShotBoard, myGameGraph, x, ++y);
			dir = 'r';
		}
		else if (urShotBoard[x - 1][y] == 10)
		{
			playersMove(urShotBoard, myGameGraph, --x, y);
			dir = 'u';
		}
		else if (urShotBoard[x][y - 1] == 10)
		{
			playersMove(urShotBoard, myGameGraph, x, --y);
			dir = 'l';
		}
	}
	else
	{
		switch (dir)
		{
		case 'd':
		{
			if (urShotBoard[x + 1][y] == 10)
			{
				playersMove(urShotBoard, myGameGraph, ++x, y);

				if (urShotBoard[x][y] == 0)
				{
					dir = '-';
					hit = false;
					break;
				}
			}
			break;
		}
		case 'r':
		{
			if (urShotBoard[x][y + 1] == 10)
			{
				playersMove(urShotBoard, myGameGraph, x, ++y);

				if (urShotBoard[x][y] == 0)
				{
					dir = '-';
					hit = false;
					break;
				}
			}
			break;
		}
		case 'u':
		{
			if (urShotBoard[x - 1][y] == 10)
			{
				playersMove(urShotBoard, myGameGraph, --x, y);

				if (urShotBoard[x][y] == 0)
				{
					dir = '-';
					hit = false;
					break;
				}
			}
			break;
		}
		case 'l':
		{
			if (urShotBoard[x][y - 1] == 10)
			{
				playersMove(urShotBoard, myGameGraph, x, --y);

				if (urShotBoard[x][y] == 0)
				{
					dir = '-';
					hit = false;
					break;
				}
			}
			break;
		}
		default:
			break;
		}
	}
}
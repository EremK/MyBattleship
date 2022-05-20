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


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


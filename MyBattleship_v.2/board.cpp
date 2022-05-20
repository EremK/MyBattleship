#include "header.h"
#include "functions.h"

void makeCleanBoard(int arrGraph[][BS])
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			arrGraph[i][j] = 10;
		}
	}
}
#include "header.h"
#include "functions.h"

bool winCheck(int gameGraph[][BS])
{
	for (int i = 0; i < BS; i++)
	{
		for (int j = 0; j < BS; j++)
		{
			if (gameGraph[i][j] == 9)
			{
				return false;
			}
		}
	}
	return true;
}
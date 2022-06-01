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

int** createMatrix(int rows, int columns)
{
	int** matrix = new int* [rows];

	for (int i = 0; i < rows; i++)
	{
		matrix[i] = new int[columns];
	}

	return matrix;
}

void removeMatrix(int** matrix, int n)
{
	for (int i = 0; i < n; i++)
	{
		delete[] matrix[i];
	}

	delete[] matrix;
}
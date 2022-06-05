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

std::string helloMenu()
{
	std::string str;

	str = "\t\t    Greetings, dear player!\n  You are now in my game \"Battleship\" \n\n\t\t\t\t   Key bindings:\n\nIn the current menu:\n-------------------------------------------------\n| Rt -> go to the next background \n| Lt -> go to the previous background \n| Enter -> confirm background \n| selection and go to game\n-------------------------------------------------\n\nWhile manually moving ships:\n-------------------------------------------------\n| Up -> move the ship up one cell\n| Dn -> move ship down one cell\n| Rt -> move ship to the right one cell \n| Lt -> move ship to the left one cell \n| Space -> turn the ship \n| Enter -> confirm ship location\n-------------------------------------------------";

	return str;
}
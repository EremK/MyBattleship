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

	str = "\t\t    Greetings, dear player!\n  You are now in my game \"Battleship\" \n\n\t\t\t\t   Key bindings:\n\nIn the current menu:\n-------------------------------------------------\n| Rt -> go to the next background\n| Lt -> go to the previous background\n| Enter -> confirm background\n| selection and go to game\n-------------------------------------------------\n\nWhile manually moving ships:\n-------------------------------------------------\n| Up -> move the ship up one cell\n| Dn -> move ship down one cell\n| Rt -> move ship to the right one cell\n| Lt -> move ship to the left one cell\n| Space -> turn the ship\n| Enter -> confirm ship location\n-------------------------------------------------";

	return str;
}

int StringToNumber(std::string str)
{
	int result = 0, i = 0;

	while (true)
	{
		if (str[i] == '\0')
		{
			result /= 10;
			return result;
		}
		else if (str[i] < 48 || str[i] > 57)
		{
			i++;
			continue;
		}

		result += str[i] - 48;
		result *= 10;
		i++;
	}
}


void high_score_save(int score, int player)
{
	switch (player)
	{
	case 1:
	{
		std::ofstream out("C:\\Users\\asusv\\Desktop\\ШАГ\\Основы C++\\Экзамен\\MyBattleship_v.2\\Media files\\high_score1.txt");

		if (out.is_open())
		{
			out << score;
		}

		out.close();
		break;
	}
	case 2:
	{
		std::ofstream out("C:\\Users\\asusv\\Desktop\\ШАГ\\Основы C++\\Экзамен\\MyBattleship_v.2\\Media files\\high_score2.txt");

		if (out.is_open())
		{
			out << score;
		}

		out.close();
		break;
	}
	}
}

int high_score_init(int player)
{
	std::string line;

	switch (player)
	{
	case 1:
	{
		std::ifstream in("C:\\Users\\asusv\\Desktop\\ШАГ\\Основы C++\\Экзамен\\MyBattleship_v.2\\Media files\\high_score1.txt");

		if (in.is_open())
		{
			getline(in, line);
			in.close();
		}
		return StringToNumber(line);
	}
	case 2:
	{
		std::ifstream in("C:\\Users\\asusv\\Desktop\\ШАГ\\Основы C++\\Экзамен\\MyBattleship_v.2\\Media files\\high_score2.txt");

		if (in.is_open())
		{
			getline(in, line);
			in.close();
		}
		return StringToNumber(line);
	}
	}
}


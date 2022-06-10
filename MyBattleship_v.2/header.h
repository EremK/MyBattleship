#include <SFML/Graphics.hpp>
#include <time.h>
#include <cstdlib>
#include "windows.h"
#include <iostream>
#include <string>
#include <fstream>

#define BS 10

using namespace sf;

const int ships[10] = { 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };

const int coords[8][2] = {
		{-1, 1},
		{0, 1},
		{1, 1},
		{1, 0},
		{1, -1},
		{0, -1},
		{-1, -1},
		{-1, 0}
};

enum GameStages
{
	PAUSE = -1,
	MANUAL,
	START,
	GAMEPLAY,
	FINISH
};
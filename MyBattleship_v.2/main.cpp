#include "header.h"
#include "functions.h"

int main()
{
	RenderWindow app(VideoMode(830, 830), "BATTLESHIP");
	srand(time(0));

	int myGameGraph[BS][BS] = {};
	int myShotsBoard[BS][BS];

	int urGameGraph[BS][BS] = {};
	int urShotsBoard[BS][BS];

	int w = 32;
	int gameStage = START;
	int shipsTotal = 0;
	int moveNumber = 1;
	bool gameMode = 0; // 0 - ������� -> ���������, 1 - ��������� -> ���������
	bool compIntelligence = 0; // 0 - ��������� �������, 1 - ����� ����
	bool hideEnemyBoard = 1;

	// �������� �������� � �������� �������
	Texture t, texture_background;
	t.loadFromFile("C:\\Users\\asusv\\Desktop\\���\\������ C++\\�������\\MyBattleship_v.2\\Media files\\2.jpg");
	//texture_background.loadFromFile("C:\\Users\\asusv\\Desktop\\���\\������ C++\\�������\\MyBattleship_v.2\\Media files\\Background.png"); // ��� <-
	Sprite s(t), s_background(texture_background);

	// P1 
	makeCleanBoard(myGameGraph);
	makeCleanBoard(myShotsBoard);

	// P2
	makeCleanBoard(urGameGraph);
	makeCleanBoard(urShotsBoard);
	changeShipsPlacement(urGameGraph);

	while (app.isOpen())
	{
		Vector2i pos = Mouse::getPosition(app); // 
		int x = pos.x / w;
		int y = pos.y / w;

		std::cout << x << "\t" << y << std::endl; // temp !

		Event e;

		app.clear(Color::White);

		app.draw(s_background);

		if (gameStage == START)
		{
			// ������ 1 ������� �� ��������� ���� ����
			s.setTextureRect(IntRect(11 * w, 0, w, w));
			s.setPosition(0, 0);
			s.move(30, 0);
			app.draw(s);

			// ������ 2 ������� ������������ ��������
			s.setTextureRect(IntRect(1 * w, 0, w, w));
			s.setPosition(0, 0);
			s.move(62, 0);
			app.draw(s);
			// // // // //

			// ������ �������� ������� ��� ����������� ����������� 
			//s.setTextureRect(IntRect(4 * w, 0, w, w));
			//s.setPosition(0, 0);
			//s.move(30, 410);
			//app.draw(s);
			// // // // //
		}
		else if (gameStage == GAMEPLAY || gameStage == PAUSE)
		{
			// ������ - ����� ����
			s.setTextureRect(IntRect(3 * w, 0, w, w));
			s.setPosition(0, 0);
			s.move(734, 0);
			app.draw(s);
			// // // // //
			// ������ - �����
			s.setTextureRect(IntRect(2 * w, 0, w, w));
			s.setPosition(0, 0);
			s.move(702, 0);
			app.draw(s);
			// // // // //
			// ������ - ��������/������ ��������� ����
			s.setTextureRect(IntRect(1 * w, 0, w, w));
			s.setPosition(0, 0);
			s.move(670, 0);
			app.draw(s);
			// // // // //
		}

		// ��������� �����
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				// �������� �� ������� ������ ��� ��������� ��������
				s.setTextureRect(IntRect(myGameGraph[i][j] * w, 0, w, w));
				// ������������� ��� � �������� �������...
				s.setPosition(j * w, i * w);
				s.move(30, 70); // ��������� ������� ����, ����� �������� ��������������� � ��������� ����
				app.draw(s); // ... � ������������
			}
			if (gameStage == GAMEPLAY || gameStage == PAUSE)
			{
				for (int j = 0; j < 10; j++)
				{
					s.setTextureRect(IntRect(myShotsBoard[i][j] * w, 0, w, w));
					s.setPosition(j * w, i * w);
					s.move(30, 440);
					app.draw(s);
				}

				if (!hideEnemyBoard)
				{
					for (int j = 0; j < 10; j++) // ��������� �������� ���� ������ 2
					{
						s.setTextureRect(IntRect(urGameGraph[i][j] * w, 0, w, w));
						s.setPosition(j * w, i * w);
						s.move(400, 70);
						app.draw(s);
					}
					for (int j = 0; j < 10; j++)
					{
						s.setTextureRect(IntRect(urShotsBoard[i][j] * w, 0, w, w));
						s.setPosition(j * w, i * w);
						s.move(400, 440);
						app.draw(s);
					}
				}
			}
		}

		// ������ �����

		if (gameStage == GAMEPLAY)
		{
			if (moveNumber % 2 == 0) // ��� ����������
			{
				if (compIntelligence == 0) // �� ����������
				{
					x = rand() % 9;
					y = rand() % 9;
					playersMove(urShotsBoard, myGameGraph, y, x);
					moveNumber++;
				}
				else if (gameStage == GAMEPLAY)
				{

				}
			}
		}


		//

		// �������� ������!

		if (winCheck(myGameGraph) && gameStage == GAMEPLAY)
		{
			std::cout << "Player 1 Wins!\n";
		}
		else if (winCheck(urGameGraph) && gameStage == GAMEPLAY)
		{
			std::cout << "Player 2 Wins!\n";
		}

		//

		while (app.pollEvent(e))
		{
			if (e.type == Event::Closed)
				app.close();

			if (e.type == Event::MouseButtonPressed)
			{
				if (gameStage == GAMEPLAY || gameStage == PAUSE) // �����
				{
					if (e.key.code == Mouse::Left && x == 22 && y == 0)
					{
						if (gameStage == GAMEPLAY)
						{
							gameStage = PAUSE;
						}
						else if (gameStage == PAUSE)
						{
							gameStage = GAMEPLAY;
						}
					}
				}
				if (gameStage == START)
				{
					if (e.key.code == Mouse::Left && x == 1 && y == 0 && shipsTotal == 9)
					{
						++gameStage;
						break;
					}
					else if (e.key.code == Mouse::Left && x == 2 && y == 0)
					{
						changeShipsPlacement(myGameGraph);
						shipsTotal = 9;
						break;
					}
					//else if (e.key.code == Mouse::Left && x == 1 && y == 13) // Temp, not done yet
					//{
					//	//makeCleanBoard(myGameGraph); //
					//	//makeCleanBoard(myGameLogic); //
					//	//shipsTotal = 0; // ����� ����� ���� ������.
					//	bool shipConfirm = true;
					//	int** shipCoords = createMatrix(ships[shipsTotal], 2);
					//	if (shipsTotal < 10) searchRandPlace(myGameLogic, myGameGraph, shipsTotal, shipCoords);

					//	int dx = 0;

					//	removeMatrix(shipCoords, ships[shipsTotal - 1]);
					//	break;
					//}
				}
				else if (gameStage == GAMEPLAY)
				{
					if (e.key.code == Mouse::Left && x == 21 && y == 0)
					{
						hideEnemyBoard = !hideEnemyBoard;
					}
					if (gameMode == START) // ������� -> ���������
					{
						if (e.key.code == Mouse::Left
							&& x >= 1 && x <= 10
							&& y >= 14 && y <= 23
							&& myShotsBoard[y - 14][x - 1] != 5
							&& myShotsBoard[y - 14][x - 1] != 0
							&& moveNumber % 2 != 0)
						{
							std::cout << "FF?\n";
							x -= 1;
							y -= 14;
							playersMove(myShotsBoard, urGameGraph, y, x);
							moveNumber++;
						}
					}
					//if (gameMode == 1) // ��������� -> ���������
					//{

					//}
				}
				//else if (gameStage == 1) // 3-� ���� ���� - ������.
				//{

				//}

				if (gameStage == GAMEPLAY)
				{
					if (e.key.code == Mouse::Left && x == 23 && y == 0)
					{
						makeCleanBoard(myGameGraph);
						makeCleanBoard(myShotsBoard);
						makeCleanBoard(urGameGraph);
						makeCleanBoard(urShotsBoard);
						changeShipsPlacement(urGameGraph);
						--gameStage;
						break;
					}
				}
			}

			Sleep(100);
		}

		app.display();

		Sleep(100);
	}

	return 0;
}
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
	bool gameMode = 0; // 0 - человек -> компьютер, 1 - компьютер -> компьютер
	bool compIntelligence = 0; // 0 - случайный выстрел, 1 - умная игра
	bool hideEnemyBoard = 1;
	bool hit = false;
	int t_x, t_y;
	char dir = '-';
	int** shipCoords = nullptr;
	bool shipConfirmed = true;
	bool shipIsVertical = true;

	// Загрузка текстуры и создание спрайта
	Texture t, texture_background;
	t.loadFromFile("C:\\Users\\asusv\\Desktop\\ШАГ\\Основы C++\\Экзамен\\MyBattleship_v.2\\Media files\\BS.jpg");
	//texture_background.loadFromFile("C:\\Users\\asusv\\Desktop\\ШАГ\\Основы C++\\Экзамен\\MyBattleship_v.2\\Media files\\Background.png"); // Фон <-
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

		//std::cout << x << "\t" << y << std::endl; // temp !

		Event e;

		app.clear(Color::White);

		app.draw(s_background);

		if (gameStage == START || gameStage == MANUAL)
		{
			// Кнопка 1 Переход на следующий этап игры
			s.setTextureRect(IntRect(11 * w, 0, w, w));
			s.setPosition(0, 0);
			s.move(30, 0);
			app.draw(s);

			// Кнопка 2 Сменить расположение кораблей
			s.setTextureRect(IntRect(1 * w, 0, w, w));
			s.setPosition(0, 0);
			s.move(62, 0);
			app.draw(s);
			// // // // //

			// Кнопка добавить корабль для собственной росстановки 
			s.setTextureRect(IntRect(4 * w, 0, w, w));
			s.setPosition(0, 0);
			s.move(30, 410);
			app.draw(s);
			// // // // //
		}
		else if (gameStage == GAMEPLAY || gameStage == PAUSE)
		{
			// Кнопка - новая игра
			s.setTextureRect(IntRect(3 * w, 0, w, w));
			s.setPosition(0, 0);
			s.move(734, 0);
			app.draw(s);
			// // // // //
			// Кнопка - пауза
			s.setTextureRect(IntRect(2 * w, 0, w, w));
			s.setPosition(0, 0);
			s.move(702, 0);
			app.draw(s);
			// // // // //
			// Кнопка - Показать/скрыть вражеские поля
			s.setTextureRect(IntRect(1 * w, 0, w, w));
			s.setPosition(0, 0);
			s.move(670, 0);
			app.draw(s);
			// // // // //
		}

		// Отрисвока полей
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				// Вырезаем из спрайта нужный нам квадратик текстуры
				s.setTextureRect(IntRect(myGameGraph[i][j] * w, 0, w, w));
				// Устанавливаем его в заданную позицию...
				s.setPosition(j * w, i * w);
				s.move(30, 70); // Визуально двигаем поле, чтобы избежать соприкосновения с границами окна
				app.draw(s); // ... и отрисовываем
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
					for (int j = 0; j < 10; j++) // Отрисовка игрового поля игрока 2
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

		// Логика ботов

		if (gameStage == GAMEPLAY)
		{
			if (moveNumber % 2 == 0) // Ход компьютера
			{
				if (compIntelligence == 0) // Ум компьютера
				{
					x = rand() % 9;
					y = rand() % 9;
					playersMove(urShotsBoard, myGameGraph, y, x);
					moveNumber++;
				}
				else if (compIntelligence == 1)
				{
					if (hit == false)
					{
						x = rand() % 9;
						y = rand() % 9;
						t_x = x;
						t_y = y;
						playersMove(urShotsBoard, myGameGraph, y, x);

						if (urShotsBoard[y][x] == 5)
						{
							hit = true;
						}

						moveNumber++;
					}
					else
					{
						smartBotMove(urShotsBoard, myGameGraph, t_y, t_x, hit, dir);
						moveNumber++;
					}
				}
			}
		}

		//

		// Проверка победы! // Not done yet

		if (winCheck(myGameGraph) && gameStage == GAMEPLAY)
		{
			std::cout << "Player 1 Wins!\n";
		}
		else if (winCheck(urGameGraph) && gameStage == GAMEPLAY)
		{
			std::cout << "Player 2 Wins!\n";
		}

		while (app.pollEvent(e))
		{
			if (e.type == Event::Closed)
				app.close();

			if (e.type == Event::MouseButtonPressed)
			{
				if (gameStage == GAMEPLAY || gameStage == PAUSE) // Пауза
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
				if (gameStage == START || gameStage == MANUAL)
				{
					if (e.key.code == Mouse::Left && x == 1 && y == 0 && shipsTotal == 9)
					{
						gameStage = GAMEPLAY;
						break;
					}
					else if (e.key.code == Mouse::Left && x == 2 && y == 0)
					{

						changeShipsPlacement(myGameGraph);
						shipsTotal = 9;
						break;
					}
					else if (e.key.code == Mouse::Left && x == 1 && y == 13) // Temp, not done yet // Mannaul ship placement
					{
						//makeCleanBoard(myGameGraph); //
						//makeCleanBoard(myGameLogic); //
						//shipsTotal = 0; // Нужно чтобы было девять.

						if (shipsTotal == 9) // Temp, работает не по задумке
						{
							makeCleanBoard(myGameGraph);
							shipsTotal = 0;
						}
						else
						{
							if (shipConfirmed == true)
							{
								removeMatrix(shipCoords, shipsTotal);
								shipCoords = createMatrix(ships[shipsTotal], 2);
								mannualShipPlacement(myGameGraph, shipsTotal, shipCoords);

								gameStage = MANUAL;
								shipConfirmed = false;

								if (shipsTotal == 9)
								{
									gameStage == GAMEPLAY;
									break;
								}
							}
						}
						break; // ?
					}
				}
				else if (gameStage == GAMEPLAY)
				{
					if (e.key.code == Mouse::Left && x == 21 && y == 0)
					{
						hideEnemyBoard = !hideEnemyBoard;
					}
					if (gameMode == 0) // Человек -> Компьютер
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
					//if (gameMode == 1) // Компьютер -> Компьютер
					//{

					//}
				}
				//else if (gameStage == 1) // 3-й этап игры - победа.
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

			int dx = 0, dy = 0;
			if (e.type == Event::KeyPressed && gameStage == MANUAL && shipConfirmed == false /* && shipCoords != nullptr */)
			{
				if (e.key.code == Keyboard::Left)
				{
					std::cout << "L\n";
					dy = -1;
				}
				else if (e.key.code == Keyboard::Right)
				{
					std::cout << "R\n";
					dy = 1;
				}
				else if (e.key.code == Keyboard::Up)
				{
					std::cout << "U\n";
					dx = -1;
				}
				else if (e.key.code == Keyboard::Down)
				{
					std::cout << "D\n";
					dx = 1;
				}
				//else if (e.key.code == Keyboard::Space) // Поворот корабля на 90 градусов и обратно при повторном нажатии
				//{

				//}
				else if (e.key.code == Keyboard::Enter)
				{
					std::cout << "Enter\n";
					shipsTotal++;
					shipConfirmed = true;
					break;
				}

				std::cout << "Turn 122:\n";

				if (mannualMoveCheck(myGameGraph, shipsTotal, shipCoords, dx, dy, shipIsVertical))
				{
					for (int x = 0; x < ships[shipsTotal]; x++)
					{
						myGameGraph[shipCoords[x][0]][shipCoords[x][1]] = 10;
					}

					for (int z = 0; z < ships[shipsTotal]; z++)
					{
						shipCoords[z][0] += dx;
						shipCoords[z][1] += dy;
					}

					for (int x = 0; x < ships[shipsTotal]; x++)
					{
						myGameGraph[shipCoords[x][0]][shipCoords[x][1]] = 9;
					}
				}

				dx = 0, dy = 0;
			}

			Sleep(100);
		}

		app.display();

		Sleep(100);
	}

	//removeMatrix(shipCoords);

	return 0;
}


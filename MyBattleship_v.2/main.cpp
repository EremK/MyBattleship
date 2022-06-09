#include "header.h"
#include "functions.h"
#pragma warning(disable: 4996)

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
	bool hit = false, hit0 = false;
	int t_x, t_y, t_x0, t_y0;
	bool opositeDirCheck = false, opositeDirCheck0 = false;
	char dir = '-', dir0 = '-';
	int** shipCoords = nullptr;
	bool shipConfirmed = true;
	bool shipIsVertical = true;
	bool textPause = false;
	int scoreP1 = high_score_init(1), scoreP2 = high_score_init(2);

	// Загрузка текстуры и создание спрайта
	Texture t, texture_background;
	t.loadFromFile("C:\\Users\\asusv\\Desktop\\ШАГ\\Основы C++\\Экзамен\\MyBattleship_v.2\\Media files\\BS_4.jpg");
	texture_background.loadFromFile("C:\\Users\\asusv\\Desktop\\ШАГ\\Основы C++\\Экзамен\\MyBattleship_v.2\\Media files\\bg5.jpg"); // Фон <-
	Sprite s(t), s_background(texture_background);

	Font font;//шрифт 
	font.loadFromFile("robosapien.ttf");//передаем нашему шрифту файл шрифта
	Text text("", font, 17);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	Text helloTxt("", font, 31);
	text.setColor(Color::Blue);//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый
	helloTxt.setColor(Color::Cyan);
	text.setStyle(sf::Text::Bold);//жирный текст. по умолчанию он "худой":))
	helloTxt.setStyle(sf::Text::Bold);

	// P1 
	makeCleanBoard(myGameGraph);
	makeCleanBoard(myShotsBoard);

	// P2
	makeCleanBoard(urGameGraph);
	makeCleanBoard(urShotsBoard);
	changeShipsPlacement(urGameGraph);

	int currentBackground = 0;
	bool backgroundWasChanged = false;

	while (app.isOpen())
	{
		Event e;
		bool goToTheNextStep = false;
		app.draw(s_background);

		helloTxt.setString(helloMenu());//задает строку тексту
		helloTxt.setPosition(135, 45);
		app.draw(helloTxt);//рисую этот текст

		// Начальный экран, выбор фона
		while (app.pollEvent(e))
		{
			if (e.type == Event::Closed)
				app.close();

			if (e.type == Event::KeyPressed)
			{
				if (e.key.code == Keyboard::Left)
				{
					currentBackground--;
					if (currentBackground < 0)
						currentBackground = 5;
					backgroundWasChanged = true;
					break;
				}
				else if (e.key.code == Keyboard::Right)
				{
					currentBackground++;
					if (currentBackground > 5)
						currentBackground = 0;
					backgroundWasChanged = true;
					break;
				}
				else if (e.key.code == Keyboard::Enter)
				{
					goToTheNextStep = true;
					break;
				}
			}
		}

		if (currentBackground == 0 && backgroundWasChanged)
		{
			texture_background.loadFromFile("C:\\Users\\asusv\\Desktop\\ШАГ\\Основы C++\\Экзамен\\MyBattleship_v.2\\Media files\\bg3.jpg");
			Sprite s_background(texture_background);
		}
		else if (currentBackground == 1 && backgroundWasChanged)
		{
			texture_background.loadFromFile("C:\\Users\\asusv\\Desktop\\ШАГ\\Основы C++\\Экзамен\\MyBattleship_v.2\\Media files\\bg2.jpg");
			Sprite s_background(texture_background);
		}
		else if (currentBackground == 2 && backgroundWasChanged)
		{
			texture_background.loadFromFile("C:\\Users\\asusv\\Desktop\\ШАГ\\Основы C++\\Экзамен\\MyBattleship_v.2\\Media files\\bg1.png");
			Sprite s_background(texture_background);
		}
		else if (currentBackground == 3 && backgroundWasChanged)
		{
			texture_background.loadFromFile("C:\\Users\\asusv\\Desktop\\ШАГ\\Основы C++\\Экзамен\\MyBattleship_v.2\\Media files\\bg4.jpg");
			Sprite s_background(texture_background);
		}
		else if (currentBackground == 4 && backgroundWasChanged)
		{
			texture_background.loadFromFile("C:\\Users\\asusv\\Desktop\\ШАГ\\Основы C++\\Экзамен\\MyBattleship_v.2\\Media files\\bg5.jpg");
			Sprite s_background(texture_background);
		}
		else if (currentBackground == 5 && backgroundWasChanged)
		{
			texture_background.loadFromFile("C:\\Users\\asusv\\Desktop\\ШАГ\\Основы C++\\Экзамен\\MyBattleship_v.2\\Media files\\bg6.jpg");
			Sprite s_background(texture_background);
		}

		app.display();

		if (goToTheNextStep)
			break;

		Sleep(250);
	}

	while (app.isOpen())
	{
		Vector2i pos = Mouse::getPosition(app); // 
		int x = pos.x / w;
		int y = pos.y / w;

		std::cout << x << "\t" << y << std::endl; // temp !

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

			// Кнопка 3 добавить корабль для собственной росстановки 
			s.setTextureRect(IntRect(4 * w, 0, w, w));
			s.setPosition(0, 0);
			s.move(30, 410);
			app.draw(s);
			// // // // //

			// Кнопка 4 Изменить сложность бота-противника 
			s.setTextureRect(IntRect(7 * w, 0, w, w));
			s.setPosition(0, 0);
			s.move(286, 0);
			app.draw(s);
			// // // // //

			// Кнопка 5 включить режим бот против бота
			s.setTextureRect(IntRect(8 * w, 0, w, w));
			s.setPosition(0, 0);
			s.move(318, 0);
			app.draw(s);
			// // // // //
		}
		else if (gameStage == GAMEPLAY || gameStage == PAUSE || gameStage == FINISH)
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
			s.setTextureRect(IntRect(6 * w, 0, w, w));
			s.setPosition(0, 0);
			s.move(670, 0);
			app.draw(s);
			// // // // //
			helloTxt.setString("P1 score:");
			helloTxt.setPosition(10, 785);
			app.draw(helloTxt);
			helloTxt.setString(std::to_string(scoreP1));
			helloTxt.setPosition(145, 786);
			app.draw(helloTxt);
			// // // // //
			helloTxt.setString("P2 score:");
			helloTxt.setPosition(635, 785);
			app.draw(helloTxt);
			helloTxt.setString(std::to_string(scoreP2));
			helloTxt.setPosition(780, 786);
			app.draw(helloTxt);
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
			if (gameStage == GAMEPLAY || gameStage == PAUSE || gameStage == FINISH)
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


		//- - - - - - - -
		// Проверка победы! // Not done yet
		if (winCheck(urGameGraph) && gameStage == GAMEPLAY)
		{
			std::cout << "Player 1 Wins!\n";
			++scoreP1;
			high_score_save(scoreP1, 1);
			gameStage = FINISH;
		}
		else if (winCheck(myGameGraph) && gameStage == GAMEPLAY)
		{
			std::cout << "Player 2 Wins!\n";
			++scoreP2;
			high_score_save(scoreP2, 2);
			gameStage = FINISH;
		}
		//- - - - - - - -

		while (app.pollEvent(e))
		{
			if (e.type == Event::Closed)
				app.close();

			if (e.type == Event::MouseButtonPressed)
			{
				if (gameStage == GAMEPLAY || gameStage == PAUSE || gameStage == FINISH) // Пауза
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
					else if (e.key.code == Mouse::Left && x == 21 && y == 0)
					{
						hideEnemyBoard = !hideEnemyBoard;
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
					else if (e.key.code == Mouse::Left && x == 9 && y == 0) // Меняем сложность бота-противника
					{
						if (compIntelligence == 0)
						{
							text.setString("Enemy bot is smart");//задает строку тексту
							text.setPosition(100, 7);
							app.draw(text);//рисую этот текст
							textPause = true;
							compIntelligence = 1;
						}
						else if (compIntelligence == 1)
						{
							text.setString(" Enemy bot is dumb");//задает строку тексту
							text.setPosition(100, 7);
							app.draw(text);//рисую этот текст
							textPause = true;
							compIntelligence = 0;
						}


					}
					else if (e.key.code == Mouse::Left && x == 10 && y == 0) // Ставим режим игры бот против бота или наоборот
					{
						if (gameMode == 0)
						{
							text.setString("\t  Gamemode:\n\t  Bot VS Bot");//задает строку тексту
							text.setPosition(100, 0);
							app.draw(text);//рисую этот текст
							textPause = true;
							gameMode = 1;
						}
						else if (gameMode == 1)
						{
							text.setString("\t   Gamemode:\n\t Player VS Bot");//задает строку тексту
							text.setPosition(100, 0);//задаем позицию текста,
							app.draw(text);//рисую этот текст
							textPause = true;
							gameMode = 0;
						}
					}
					else if (e.key.code == Mouse::Left && x == 1 && y == 13)
					{
						if (shipsTotal == 9)
						{
							makeCleanBoard(myGameGraph);
							shipsTotal = 0;
						}

						std::cout << "Hmmmm\n";

						if (shipConfirmed == true)
						{
							//removeMatrix(shipCoords, shipsTotal);
							std::cout << "Err1\n"; //
							shipCoords = createMatrix(ships[shipsTotal], 2);
							std::cout << "Err2\n"; // 
							mannualShipPlacement(myGameGraph, shipsTotal, shipCoords);
							std::cout << "Err3\n"; //
							gameStage = MANUAL;
							shipConfirmed = false;

							if (shipsTotal == 9)
							{
								gameStage = GAMEPLAY;
								break;
							}
						}

						std::cout << "Rrrrrrr\n";

						break;
					}
				}
				else if (gameStage == GAMEPLAY && gameMode == 0)
				{
					// Человек -> Компьютер

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

				if (gameStage == GAMEPLAY || gameStage == PAUSE || gameStage == FINISH)
				{
					if (e.key.code == Mouse::Left && x == 23 && y == 0)
					{
						makeCleanBoard(myGameGraph);
						makeCleanBoard(myShotsBoard);
						makeCleanBoard(urGameGraph);
						makeCleanBoard(urShotsBoard);
						changeShipsPlacement(urGameGraph);
						gameStage = START;
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
				else if (e.key.code == Keyboard::Space) // Поворот корабля на 90 градусов и обратно при повторном нажатии
				{
					std::cout << "Space\n";
					shipIsVertical = turnShip(myGameGraph, shipsTotal, shipCoords, shipIsVertical);
				}
				else if (e.key.code == Keyboard::Enter)
				{
					std::cout << "Enter1.0\n";
					++shipsTotal;
					shipConfirmed = true;
					shipIsVertical = true;
					std::cout << "Enter2.0\n";
					if (shipsTotal == 9)
						gameStage = GAMEPLAY;
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

			Sleep(10);
		}

		//---------------
		// Логика ботов

		if (gameStage == GAMEPLAY)
		{
			if (gameMode == 1 && moveNumber % 2 != 0 && compIntelligence == 0) // Компьютер -> Компьютер
			{
				randomShot(myShotsBoard, urGameGraph, x, y);
				++moveNumber;
				Sleep(1000);
			}
			else if (gameMode == 1 && moveNumber % 2 != 0 && compIntelligence == 1)
			{
				if (hit0 == false)
				{
					randomShot(myShotsBoard, urGameGraph, x, y);
					t_x0 = x;
					t_y0 = y;
					playersMove(myShotsBoard, urGameGraph, y, x);

					if (myShotsBoard[y][x] == 5)
					{
						hit0 = true;
					}

					++moveNumber;
				}
				else
				{
					smartBotMove(myShotsBoard, urGameGraph, opositeDirCheck0, t_y0, t_x0, hit0, dir0);
					++moveNumber;
				}
				Sleep(1000);
			}

			if (moveNumber % 2 == 0) // Ход компьютера
			{
				if (compIntelligence == 0) // Ум компьютера
				{
					randomShot(urShotsBoard, myGameGraph, x, y);
					++moveNumber;
				}
				else if (compIntelligence == 1)
				{
					if (hit == false)
					{
						randomShot(urShotsBoard, myGameGraph, x, y);
						t_x = x;
						t_y = y;
						playersMove(urShotsBoard, myGameGraph, y, x);

						if (urShotsBoard[y][x] == 5)
						{
							hit = true;
						}

						++moveNumber;
					}
					else
					{
						smartBotMove(urShotsBoard, myGameGraph, opositeDirCheck, t_y, t_x, hit, dir);
						++moveNumber;
					}
				}
			}
		}
		//---------------

		app.display();

		if (textPause)
		{
			Sleep(2000);
			textPause = false;
		}

		Sleep(100);
	}

	//removeMatrix(shipCoords);

	return 0;
}
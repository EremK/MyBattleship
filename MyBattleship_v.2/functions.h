//

void makeCleanBoard(int arrGraph[][BS]);

bool placeShips(int arrGraph[][BS], int rands[], int i, int j, int counter);

void changeShipsPlacement(int arrGraph[][BS]);

void playersMove(int myShotBoard[][BS], int urGameGraph[][BS], int x, int y);

bool winCheck(int gameGraph[][BS]);

void smartBotMove(int urShotBoard[][BS], int myGameGraph[][BS], bool& opositeDirCheck, int& x, int& y, bool& hit, char& dir);

int** createMatrix(int rows, int columns);

void removeMatrix(int** matrix, int n);

bool placeShips(int arrGraph[][BS], int rands[], int i, int j, int counter, int** shipCoords);

void mannualShipPlacement(int arrGraph[][BS], int counter, int** shipCoords);

bool mannualMoveCheck(int arrGraph[][BS], int counter, int** shipCoords, int dx, int dy, bool shipIsVertical);

bool turnShip(int arrGraph[][BS], int counter, int** shipCoords, bool shipIsVertical);

std::string helloMenu();

void randomShot(int urShotBoard[][BS], int myGameGraph[][BS], int& x, int& y);

void high_score_save(int score, int player);

int high_score_init(int player);
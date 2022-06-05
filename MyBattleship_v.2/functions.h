//

void makeCleanBoard(int arrGraph[][BS]);

bool placeShips(int arrGraph[][BS], int rands[], int i, int j, int counter);

void changeShipsPlacement(int arrGraph[][BS]);

void playersMove(int myShotBoard[][BS], int urGameGraph[][BS], int x, int y);

bool winCheck(int gameGraph[][BS]);

void smartBotMove(int urShotBoard[][BS], int myGameGraph[][BS], int& x, int& y, bool& hit, char& dir);

int** createMatrix(int rows, int columns);

void removeMatrix(int** matrix, int n);

bool placeShips(int arrGraph[][BS], int rands[], int i, int j, int counter, int** shipCoords);

void mannualShipPlacement(int arrGraph[][BS], int counter, int** shipCoords);

bool mannualMoveCheck(int arrGraph[][BS], int counter, int** shipCoords, int dx, int dy, bool shipIsVertical);

bool turnShip(int arrGraph[][BS], int counter, int** shipCoords, bool shipIsVertical);

std::string helloMenu();
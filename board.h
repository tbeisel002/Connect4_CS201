#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED

void printBoard(int *board, int size);
void placeMove(int *board, int turn, int column, int size);
void createBoard(int *board, int size);
int checkGameState(int *board, int size, int col, int height);
int colFull(int *board, int column, int size);
int getPrevHeight(int *board, int size, int column);

#endif

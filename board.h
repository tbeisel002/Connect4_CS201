#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED

void printBoard(int *board, int size);
void placeMove(int *board, int turn, int column, int size);
void createBoard(int *board, int size);

#endif

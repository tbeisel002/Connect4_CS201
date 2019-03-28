/*
* In this header file are brief descriptions for each public function. For more
* detailed descriptions, see board.c
*/

#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED

/*
* prints the connect 4 board
*/
void printBoard(int *board, int size);

/*
* place a move for the given player in the given column on the board
*/
void placeMove(int *board, int turn, int column, int size);

/*
* sets all the values in the board to 0
*/
void createBoard(int *board, int size);

/*
* Checks to see if the most recent move caused that player to win
*/
int checkGameState(int *board, int size, int col, int height);

/*
* checks to see if a given column is full
*/
int colFull(int *board, int column, int size);

/*
* returns the height of the previously played token
*/
int getPrevHeight(int *board, int size, int column);

#endif

/*
* In this header file are brief descriptions for each public function. For more
* detailed descriptions, see inputOutput.c
*/

#ifndef INPUTOUTPUT_H_INCLUDED
#define INPUTOUTPUT_H_INCLUDED

/*
* Prints the menu and returns the users input choice
*/
int printMenu();

/*
* Prompts the user for the board size and returns the size
*/
int getBoardSize();

/*
* Prompts the user for a column to play in and returns the selected column along with col height
*/
int * promptPlayerMove(int turnCount, int size, int *board);

/*
* Prints the win counts for player 1 and 2 and returns the users choice on whether or
* not to reset these stats.
*/
char printPvpWins(int p1Wins, int p2Wins);

/*
* Prints the win counts for player 1 and the cpu and returns the users choice on whether or
* not to reset these stats.
*/
char printPvcWins(int pWins, int cWins);

#endif

#ifndef INPUTOUTPUT_H_INCLUDED
#define INPUTOUTPUT_H_INCLUDED

int printMenu();
int getBoardSize();
int * promptPlayerMove(int turnCount, int size, int *board);
char printPvpWins(int p1Wins, int p2Wins);
char printPvcWins(int pWins, int cWins);
int verifyIntInRange(char *input, int low, int high);

#endif

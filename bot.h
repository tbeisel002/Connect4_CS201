/*
* In this header file are brief descriptions for each public function. For more
* detailed descriptions, see bot.c
*/
#ifndef BOT_H_INCLUDED
#define BOT_H_INCLUDED

/*
* The recursive call into the minimax algorithm
*/
int * minAlg(int *board, int boardSize,int depth, int moveCount, int col,
  int height, int alpha, int beta, int colOrder[]);

#endif

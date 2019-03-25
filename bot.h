#ifndef BOT_H_INCLUDED
#define BOT_H_INCLUDED
#include "position.h"

int * minAlg(int *board, int boardSize,int depth, int moveCount, int col,
  int height, int alpha, int beta, int colOrder[]);
int * maxAlg(int *board, int boardSize,int depth, int moveCount, int col,
  int height, int alpha, int beta, int colOrder[]);

#endif
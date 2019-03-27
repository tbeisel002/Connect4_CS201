#include "bot.h"
#include "board.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int * maxAlg(int *board, int size, int depth, int moveCount, int col, int height,
  int alpha, int beta, int colOrder[]) {
  static int baseMaxArr[2]; //static array to be retuned if base case met
  static int returnMax[2]; // static array to be returned if not base case
  int max[2]; // non-static array for non base case operations within function
  int baseMaxArrInternal[2]; // non-static array for base case operations within function
  int gameOver = checkGameState((int *)board, size, col, height);
  *baseMaxArrInternal = col;
  if(gameOver == 1) {
    *(baseMaxArrInternal+1) = (size * size) - depth;
    baseMaxArr[0] = *baseMaxArrInternal;
    baseMaxArr[1] = *(baseMaxArrInternal+1);
    return baseMaxArr;
  }
  else if(gameOver == 2) {
    *(baseMaxArrInternal+1) = depth - (size * size);
    baseMaxArr[0] = *baseMaxArrInternal;
    baseMaxArr[1] = *(baseMaxArrInternal+1);
    return baseMaxArr;
  }
  else if(moveCount >= size * size) {
    *(baseMaxArrInternal+1) = 0;
    baseMaxArr[0] = *baseMaxArrInternal;
    baseMaxArr[1] = *(baseMaxArrInternal+1);
    return baseMaxArr;
  }
  *(max) = -1;
  *(max+1) = (depth+1) - (size * size);
  if(alpha > *(max+1)) {
    alpha = *(max+1);
    if(alpha >= beta) { // prune this exploration
      baseMaxArr[0] = *max;
      baseMaxArr[1] = beta;
      return baseMaxArr;
    }
  }
  if(depth > 6) { // Only go up to depth of 5 (0-4)
    baseMaxArr[0] = *baseMaxArrInternal;
    baseMaxArr[1] = (depth+1) - (size * size);
    return baseMaxArr;
  }

  int i, colHeight;
  for(i = 0; i < size; i++) {
    colHeight = colFull((int *)board, colOrder[i], size);
    if(colHeight != -1) {
      //int board2 [size][size];
      int *board2 = (int*)malloc(sizeof(int)*size*size);
      memcpy(board2, (int *)board, sizeof (int) * size * size);
      placeMove((int *)board2, 1, colOrder[i], size);

      int *maxCurr = minAlg((int *)board2, size, depth+1, moveCount+1, colOrder[i],
      colHeight, alpha, beta, colOrder);

      if(*(maxCurr+1) >= beta) { //prune if better than what were looking for
        returnMax[1] = *(maxCurr+1);
        returnMax[0] = colOrder[i];
        free(board2);
        return returnMax;
      }
      else if(*(maxCurr+1) > alpha) {
        alpha = *(maxCurr+1);
        *max = colOrder[i];
      }
      free(board2);
    }
  }

  returnMax[0] = *max;
  returnMax[1] = alpha;
  return returnMax;
}

int * minAlg(int *board, int size, int depth, int moveCount, int col, int height,
  int alpha, int beta, int colOrder[]) {
  static int baseMinArr[2]; //static array to be retuned if base case met
  static int returnMin[2]; //static array to be returned if not base case
  int min[2]; //non-static array for non base case operations within function
  int baseMinArrInternal[2]; //non-static array for base case operations within function
  int gameOver = checkGameState((int *)board, size, col, height);
  *baseMinArrInternal = col;
  if(gameOver == 1) {
    *(baseMinArrInternal+1) = (size * size) - depth;
    baseMinArr[0] = *baseMinArrInternal;
    baseMinArr[1] = *(baseMinArrInternal+1);
    return baseMinArr;
  }
  else if(gameOver == 2) {
    *(baseMinArrInternal+1)  = depth - (size * size);
    baseMinArr[0] = *baseMinArrInternal;
    baseMinArr[1] = *(baseMinArrInternal+1);
    return baseMinArr;
  }
  else if(moveCount >= size * size) {
    *(baseMinArrInternal+1)  = 0;
    baseMinArr[0] = *baseMinArrInternal;
    baseMinArr[1] = *(baseMinArrInternal+1);
    return baseMinArr;
  }
  *min = -2;
  *(min+1) = (size * size) - (depth+1); //upper bound for score
  if(beta > *(min+1)) {
    beta = *(min+1);
    if(beta <= alpha) {
      baseMinArr[0] = *min;
      baseMinArr[1] = beta;
      return baseMinArr;
    }
  }
  if(depth > 6) {
    baseMinArr[0] = *baseMinArrInternal;
    baseMinArr[1] = (size * size) - (depth+1);
    return baseMinArr;
  }

  int i, colHeight;
  for(i = 0; i < size; i++) {
    colHeight = colFull((int *)board, colOrder[i], size);
      if(colHeight != -1) {
        //int board2 [size][size];
        int *board2 = (int*)malloc(sizeof(int)*size*size);
        memcpy(board2, (int *)board, sizeof (int) * size * size);
        placeMove((int *)board2, 2, colOrder[i], size);

        int *minCurr = maxAlg((int *)board2, size, depth+1, moveCount+1, colOrder[i],
        colHeight, alpha, beta, colOrder);
        if(*(minCurr+1) <= alpha) {
          returnMin[1] = *(minCurr+1);
          returnMin[0] = colOrder[i];
          free(board2);
          return returnMin;
        }
        else if(*(minCurr+1) < beta) {
          beta = *(minCurr+1);
          *min = colOrder[i];
        }
        free(board2);
      }
  }
  returnMin[0] = *min;
  returnMin[1] = beta;
  return returnMin;
}

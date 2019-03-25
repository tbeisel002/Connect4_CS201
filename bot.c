#include "bot.h"
#include "position.h"
#include "board.h"
#include <stdio.h>
#include <string.h>

int * maxAlg(int *board, int size, int depth, int moveCount, int col, int height,
  int alpha, int beta, int colOrder[]) {
  static int returnMaxArr[2]; //static arrays to be retuned
  int max[2];
  int maxArr[2];
  static int returnMax[2];
  int gameOver = checkGameState((int *)board, size, col, height);
  *maxArr = col;
  if(gameOver == 1) {
    *(maxArr+1) = (size * size) - depth;
    returnMaxArr[0] = *maxArr;
    returnMaxArr[1] = *(maxArr+1);
    return returnMaxArr;
  }
  else if(gameOver == 2) {
    *(maxArr+1) = depth - (size * size);
    returnMaxArr[0] = *maxArr;
    returnMaxArr[1] = *(maxArr+1);
    return returnMaxArr;
  }
  else if(moveCount >= size * size) {
    *(maxArr+1) = 0;
    returnMaxArr[0] = *maxArr;
    returnMaxArr[1] = *(maxArr+1);
    return returnMaxArr;
  }
  *(max) = -1;
  *(max+1) = (depth+1) - (size * size);
  if(alpha > *(max+1)) {
    alpha = *(max+1);
    if(alpha >= beta) { // prune this exploration
      //printf("holla\n");
      returnMaxArr[0] = *max;
      returnMaxArr[1] = beta;
      return returnMaxArr;
    }
  }
  if(depth > 4) {
    returnMaxArr[0] = *maxArr;
    returnMaxArr[1] = (depth+1) - (size * size);
    return returnMaxArr;
  }

  int i, colHeight;
  for(i = 0; i < size; i++) {
    colHeight = colFull((int *)board, colOrder[i], size);
    if(colHeight != -1) {
      int board2 [size][size];
      memcpy(board2, (int *)board, sizeof (int) * size * size);
      placeMove((int *)board2, 1, colOrder[i], size);

      int *maxCurr = minAlg((int *)board2, size, depth+1, moveCount+1, colOrder[i],
      colHeight, alpha, beta, colOrder);

      if(*(maxCurr+1) >= beta) { //prune if better than what were looking for
        //printf("yowdy\n");
        returnMax[1] = *(maxCurr+1);
        returnMax[0] = colOrder[i];
        return returnMax;
      }
      else if(*(maxCurr+1) > alpha) {
        alpha = *(maxCurr+1);
        *max = colOrder[i];
      }
    }
  }

  returnMax[0] = *max;
  returnMax[1] = alpha;
  return returnMax;
}

int * minAlg(int *board, int size, int depth, int moveCount, int col, int height,
  int alpha, int beta, int colOrder[]) {
  static int returnMinArr[2]; //static arrays to be retuned
  int min[2];
  int minArr[2];
  static int returnMin[2];
  int gameOver = checkGameState((int *)board, size, col, height);
  *minArr = col;
  if(gameOver == 1) {
    *(minArr+1) = (size * size) - depth;
    returnMinArr[0] = *minArr;
    returnMinArr[1] = *(minArr+1);
    return returnMinArr;
  }
  else if(gameOver == 2) {
    *(minArr+1)  = depth - (size * size);
    returnMinArr[0] = *minArr;
    returnMinArr[1] = *(minArr+1);
    return returnMinArr;
  }
  else if(moveCount >= size * size) {
    *(minArr+1)  = 0;
    returnMinArr[0] = *minArr;
    returnMinArr[1] = *(minArr+1);
    return returnMinArr;
  }
  *min = -2;
  *(min+1) = (size * size) - (depth+1); //upper bound for score
  if(beta > *(min+1)) {
    beta = *(min+1);
    if(beta <= alpha) {
      //printf("holla\n");
      returnMinArr[0] = *min;
      returnMinArr[1] = beta;
      return returnMinArr;
    }
  }
  if(depth > 4) {
    returnMinArr[0] = *minArr;
    returnMinArr[1] = (size * size) - (depth+1);
    return returnMinArr;
  }

  int i, colHeight;
  for(i = 0; i < size; i++) {
    colHeight = colFull((int *)board, colOrder[i], size);
      if(colHeight != -1) {
        int board2 [size][size];
        memcpy(board2, (int *)board, sizeof (int) * size * size);
        placeMove((int *)board2, 2, colOrder[i], size);

        int *minCurr = maxAlg((int *)board2, size, depth+1, moveCount+1, colOrder[i],
        colHeight, alpha, beta, colOrder);
        //if(moveCount == moveCount + depth) {
          //printf("%d    %d    %d    %d\n", colOrder[i], *(minCurr + 1), alpha, beta);
        //}
        if(*(minCurr+1) <= alpha) {
          returnMin[1] = *(minCurr+1);
          returnMin[0] = colOrder[i];
          return returnMin;
        }
        else if(*(minCurr+1) < beta) {
          beta = *(minCurr+1);
          *min = colOrder[i];
        }
      }
  }
  returnMin[0] = *min;
  returnMin[1] = beta;
  return returnMin;
}

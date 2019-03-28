/************************************************
* bot.c file
* This file contains the 2 recursive min and max depth first seach algorithms
* that are used to determine the next best move for the ai. The main method in
* main.c calls minAlg, and then minAlg and maxAlg call each other recursively until
* the best move is found, or up to a depth of 6. Once a depth of 6 is reached, the
* the lower bound for possible scores if the search down that path were to continue
* is returned. The algorithm uses an alpha beta variation of minimax (which means
* that if a searches upper bound is less than a move's score thats already been found,
* that search is pruned off) and carries out its depth first search middle out with
* respect to the columns of the board. This is done because theoretically in
* connect 4, the center columns are the most valuable. Thus, searching them first
* in combination with the alpha beta approach drastically cuts down the search
* time it takes to find the best move. This also explains why the ai always plays
* the centermost available column if all columns are scored equal after a depth of
* 6. The function returns an array in the form of [columnOfBestScore, bestScore].
*/
#include "bot.h"
#include "board.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Private Functions
static int * maxAlg(int *board, int size, int depth, int moveCount, int col, int height,
  int alpha, int beta, int colOrder[]);

/*
* minAlg Function
* *board - the 2d array that contains the current connect 4 board
* size - the size of the board. Eg 10 for a 10x10 board
* depth - the depth of the recursive call (first call is 0)
* moveCount - how many moves have been played. Keeping this as a parameter instead
              of computing it each time when evaluating end game state to determine
              when a tie is reached speeds up run time.
* col - the column that has just been played
* height - the row that most recent token was played in (same as moveCount)
* alpha - the lower bound for score that were searching for
* beta - the upper bound for score that were searching for
* colOrder[] - the altered column order to search (middle out). See top of file
               description for why this is so beneficial.
* return - an array in the form of [columnOfBestScore, bestScore]
****
****
* minAlg simulates the cpu playing in each column and recursively calls
* maxAlg to simulate the users play. It always picks the lowest
* possible score where the user winning = (size * size) - depth and the cpu
* winning = depth - (size * size). Once a depth of 6 is reached, the upper bound
* for the score down that path is returned. If a paths upper bound is lower than
* the lowest score found yet. That upper bound is returned and the rest of the
* search is pruned off.
*/
int * minAlg(int *board, int size, int depth, int moveCount, int col, int height,
  int alpha, int beta, int colOrder[]) {
  static int baseMinArr[2]; //static array to be retuned if base case met
  static int returnMin[2]; //static array to be returned if not base case
  int min[2]; //non-static array for non base case operations within function
  int baseMinArrInternal[2]; //non-static array for base case operations within function
  int gameOver = checkGameState((int *)board, size, col, height);
  *baseMinArrInternal = col;
  if(gameOver == 1) { // if the user has won (base case)
    *(baseMinArrInternal+1) = (size * size) - depth;
    baseMinArr[0] = *baseMinArrInternal;
    baseMinArr[1] = *(baseMinArrInternal+1);
    return baseMinArr;
  }
  else if(gameOver == 2) { // if the cpu has won (base case)
    *(baseMinArrInternal+1)  = depth - (size * size);
    baseMinArr[0] = *baseMinArrInternal;
    baseMinArr[1] = *(baseMinArrInternal+1);
    return baseMinArr;
  }
  else if(moveCount >= size * size) { // if its a tie (base case)
    *(baseMinArrInternal+1)  = 0;
    baseMinArr[0] = *baseMinArrInternal;
    baseMinArr[1] = *(baseMinArrInternal+1);
    return baseMinArr;
  }
  *min = -2;
  *(min+1) = (size * size) - (depth+1); //upper bound for score
  if(beta > *(min+1)) {
    beta = *(min+1); // if beta > upper bound, beta = upper bound
    if(beta <= alpha) { // if the upper bound <= previousky found lower bound, return (prune)
      baseMinArr[0] = *min;
      baseMinArr[1] = beta;
      return baseMinArr;
    }
  }
  if(depth > 6) { // if depth of 6 reached, return upper bound (base case)
    baseMinArr[0] = *baseMinArrInternal;
    baseMinArr[1] = (size * size) - (depth+1);
    return baseMinArr;
  }

  int i, colHeight;
  for(i = 0; i < size; i++) {
    colHeight = colFull((int *)board, colOrder[i], size);
      if(colHeight != -1) { // if the column is not already full
        int *board2 = (int*)malloc(sizeof(int)*size*size); // make a copy of the board and
        memcpy(board2, (int *)board, sizeof (int) * size * size); // place token in
        placeMove((int *)board2, 2, colOrder[i], size); // centermost unsearched column

        int *minCurr = maxAlg((int *)board2, size, depth+1, moveCount+1, colOrder[i],
        colHeight, alpha, beta, colOrder); // recursive call to simulate user after cpu plays
        if(*(minCurr+1) <= alpha) { // if returned score is lower than previous lower
          returnMin[1] = *(minCurr+1); // lower bound. Return returned score (prune)
          returnMin[0] = colOrder[i];
          free(board2);
          return returnMin;
        }
        else if(*(minCurr+1) < beta) { // if returned score is less than previous
          beta = *(minCurr+1); // upper bound, update new upper bound to returned score
          *min = colOrder[i];
        }
        free(board2);
      }
  }
  returnMin[0] = *min;
  returnMin[1] = beta;
  return returnMin;
}

/*
* maxAlg Function
* *board - the 2d array that contains the current connect 4 board
* size - the size of the board. Eg 10 for a 10x10 board
* depth - the depth of the recursive call (first call is 0)\
* moveCount - how many moves have been played. Keeping this as a parameter instead
              of computing it each time when evaluating end game state to determine
              when a tie is reached speeds up run time.
* col - the column that has just been played
* height - the row that most recent token was played in
* alpha - the lower bound for score that were searching for
* beta - the upper bound for score that were searching for
* colOrder[] - the altered column order to search (middle out). See top of file
               description for why this is so beneficial.
* return - an array in the form of [columnOfBestScore, bestScore]
****
****
* maxAlg simulates the user playing in each column and recursively calls
* minAlg to simulate the cpu's play. It always picks the highest
* possible score where the user winning = (size * size) - depth and the cpu
* winning = depth - (size * size). Once a depth of 6 is reached, the lower bound
* for the score down that path is returned. If a paths lower bound is higher than
* the highest score found yet. That upper bound is returned and the rest of the
* search is pruned off.
*/
static int * maxAlg(int *board, int size, int depth, int moveCount, int col, int height,
  int alpha, int beta, int colOrder[]) {
  static int baseMaxArr[2]; //static array to be retuned if base case met
  static int returnMax[2]; // static array to be returned if not base case
  int max[2]; // non-static array for non base case operations within function
  int baseMaxArrInternal[2]; // non-static array for base case operations within function
  int gameOver = checkGameState((int *)board, size, col, height);
  *baseMaxArrInternal = col;
  if(gameOver == 1) { // if the user has won (base case)
    *(baseMaxArrInternal+1) = (size * size) - depth;
    baseMaxArr[0] = *baseMaxArrInternal;
    baseMaxArr[1] = *(baseMaxArrInternal+1);
    return baseMaxArr;
  }
  else if(gameOver == 2) { // if the cpu has won (base case)
    *(baseMaxArrInternal+1) = depth - (size * size);
    baseMaxArr[0] = *baseMaxArrInternal;
    baseMaxArr[1] = *(baseMaxArrInternal+1);
    return baseMaxArr;
  }
  else if(moveCount >= size * size) { // if its a tie (base case)
    *(baseMaxArrInternal+1) = 0;
    baseMaxArr[0] = *baseMaxArrInternal;
    baseMaxArr[1] = *(baseMaxArrInternal+1);
    return baseMaxArr;
  }
  *(max) = -1;
  *(max+1) = (depth+1) - (size * size); // lower bound for score
  if(alpha > *(max+1)) {
    alpha = *(max+1); // if alpha > lower bound, alpha = lower bound
    if(alpha >= beta) { // if the lower bound >= previously found upper bound,
      baseMaxArr[0] = *max;
      baseMaxArr[1] = beta;
      return baseMaxArr; // return lower bound (prune)
    }
  }
  if(depth > 6) { // if depth of 6 reached, return lower bound (base case)
    baseMaxArr[0] = *baseMaxArrInternal;
    baseMaxArr[1] = (depth+1) - (size * size);
    return baseMaxArr;
  }

  int i, colHeight;
  for(i = 0; i < size; i++) {
    colHeight = colFull((int *)board, colOrder[i], size);
    if(colHeight != -1) { // if the column is not already full
      int *board2 = (int*)malloc(sizeof(int)*size*size);
      memcpy(board2, (int *)board, sizeof (int) * size * size);
      placeMove((int *)board2, 1, colOrder[i], size);

      int *maxCurr = minAlg((int *)board2, size, depth+1, moveCount+1, colOrder[i],
      colHeight, alpha, beta, colOrder); // recursive call to simulate cpu after simulated user play

      if(*(maxCurr+1) >= beta) { //prune if returned score better than what were looking for
        returnMax[1] = *(maxCurr+1);
        returnMax[0] = colOrder[i];
        free(board2);
        return returnMax;
      }
      else if(*(maxCurr+1) > alpha) { // if returned score is greater than previous
        alpha = *(maxCurr+1); // upper bound, Update upper bound
        *max = colOrder[i];
      }
      free(board2);
    }
  }

  returnMax[0] = *max;
  returnMax[1] = alpha;
  return returnMax;
}

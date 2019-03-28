/************************************************
* board.c file
* This file contains the necessary functions for interfacing with the connect 4
* board.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "board.h"

/*
* *board - the 2d array that represents the connect 4 board
* size - the size of the board
*****
*****
* createBoard sets every element in the 2d array to 0
*/
void createBoard(int *board, int size) {
  int i, j;
	for(i = 0; i < size; i++) {
		for(j = 0; j < size; j++) {
			*((board+i*size) + j) = 0;
		}
	}
}

/*
* *board - the 2d array that represents the connect 4 board
* size - the size of the board
*****
*****
* printBoard prints the 2d array with row and column numbers
*/
void printBoard(int *board,int size) {
	int i, j;
  printf("\n     ");
  for(i = 0; i < size; i++) {
    if(i < 9) {
      printf("%d  ", i+1);
    }
    else {
      printf("%d ", i+1);
    }
  }
  printf("\n");
	for(i = 0; i < size; i++) {
    if(i < 9) {
      printf("%d  - ", i+1);  //print row number
    }
    else {
      printf("%d - ", i+1);
    }
		for(j = 0; j < size; j++) {
			printf("%d  ", *((board+i*size) +j));
		}
	  printf("\n");
	}
}

/*
* *board - the 2d array that represents the connect 4 board
* turn - the token whose turn it is (1 or 2)
* column - the column to place the token in
* size - the size of the board
*****
*****
* placeMove places the correct token into the lowest open spot in the given column
*/
void placeMove(int *board, int turn, int column, int size) {
  int movePlaced = 0;
  int i = size - 1;
  while(movePlaced == 0 && i >= 0) {
    if(*((board+i*size) + column) == 0) {
      *((board+i*size) + column) = turn;
      movePlaced = 1;
    }
    i--;
  }
}

/*
* *board - the 2d array that represents the connect 4 board
* column - the column of the board to check
* size - the size of the board
* return - the int of the first row from the bottom where that column contains a 0
         - -1 if the column is full.
*****
*****
* colFull checks to see if a column is full. If theres an opening, it returns
* the first opening from the bottom. If the column is full, it returns -1.
*/
int colFull(int *board, int column, int size) {
  int i = size - 1;
  int validHeight = -1;
  while(validHeight == -1 && i >= 0) {
    if(*((board+i*size) + column) == 0) {
      validHeight = i;
    }
    i--;
  }
  return validHeight;
}

/*
* *board - the 2d array that represents the connect 4 board
* size - the size of the board
* col - the column of the board to check
* height - the height (row) of the most recently played token
* return - 1 if player 1 has won, 2 if player 2/cpu has won, or 0 if no one has won.
*****
*****
* checkGameState checks the board to see if the most recent move caused the player
* making that move to have 4 in a row. This function gets called inside of every
* recursive call of the minimax algorithm so its important that it works as efficiently
* as possible. The function counts how many same numbered tokens are immediately
* to the left, right, above, below, upper right diagonal, upper left diagonal,
* lower left diagonal, and lower right diagonal of the most recently played token.
* If left+right, above+below, diagUpperRight+diagLowerLeft, or diagUpperLeft+diagLowerRight
* add up to 4 including the most recently played token, then the game is over and
* that player has won. This is significantly faster than the common way of four
* pairs of nested for loops that check for side to side, up and down, right diag and
* left diag. For example, with a 10x10 board, the simplest nested for loop approach
* has an upper limit of O(400) and would grow exponentially with n.
* In contrast, this approach has an upper limit of O(24) regardless of board size.
* Thus, this function allows the ai to successfully handle large board sizes without
* spending hours checking the game state for every single recursive call of every
* node in the depth first search.
*/
int checkGameState(int *board, int size, int col, int height) {
    int numLeft = 0;
    int numRight = 0;
    int numDiagLowerLeft = 0;
    int numDiagLowerRight = 0;
    int numDiagUpperRight = 0;
    int numDiagUpperLeft = 0;
    int numAbove = 0;
    int numBelow = 0;
    int value = *((board+height*size) + col);
    int i, j;
    for(i = col+1; i < size; i++) { // check the number to the right
      if(*((board+height*size) + i) == value) {
        numRight++;
      }
      else {
        break;
      }
    }
    for(i = col - 1; i >= 0; i--) { // check the number to the left
      if(*((board+height*size) + i) == value) {
        numLeft++;
      }
      else {
        break;
      }
    }
    if(numLeft + numRight >= 3) { // return if found 4
      return value;
    }
    for(i = height - 1; i >= 0; i--) { // check the number above
      if(*((board+i*size) + col) == value) {
        numAbove++;
      }
      else {
        break;
      }
    }
    for(i = height + 1; i < size; i++) { // check the number below
      if(*((board+i*size) + col) == value) {
        numBelow++;
      }
      else {
        break;
      }
    }
    if(numBelow + numAbove >= 3){ // if 4 up and down
      return value;
    }

    for(i = height - 1, j = col+1; j < size && i >= 0; i--, j++) { // check diagUpperRight
        if(*((board+i*size) + j) == value) {
          numDiagUpperRight++;
        }
        else {
          break;
        }
    }
    for(i = height + 1, j = col-1; i < size && j >= 0; i++, j--) { // check diagLowerLeft
        if(*((board+i*size) + j) == value) {
          numDiagLowerLeft++;
        }
        else {
          break;
        }
    }
    if(numDiagUpperRight + numDiagLowerLeft >= 3) { // if 4 along left diagonal
      return value;
    }
    for(i = height - 1, j = col-1; j >= 0 && i >= 0; i--, j--) { // check diagUpperLeft
        if(*((board+i*size) + j) == value) {
          numDiagUpperLeft++;
        }
        else {
          break;
        }
    }
    for(i = height + 1, j = col+1; j < size && i < size; i++, j++) { // check diagLowerRight
        if(*((board+i*size) + j) == value) {
          numDiagLowerRight++;
        }
        else {
          break;
        }
    }
    if(numDiagUpperLeft + numDiagLowerRight >= 3) { // if 4 along right diagonal
      return value;
    }
    return 0;
}

/*
* *board - the 2d array that represents the connect 4 board
* column - the column of the board to check
* size - the size of the board
* return - the int of the first row from the bottom where that column contains a 0
         - -1 if the column is full.
*****
*****
* getPrevHeight gets the height of the most recently played spot in a column for
* the cpu. This is used to make the checkGameState function a little easier when
* called from the main method.
*/
int getPrevHeight(int *board, int size, int column) {
  int i = 0;
  int exists = -1;
  while(exists == -1 && i < size) {
    if(*((board+i*size) + column) == 2) {
      exists = i;
    }
    i++;
  }
  return exists;
}

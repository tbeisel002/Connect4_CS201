#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "board.h"


void createBoard(int *board, int size) {
  int i, j;
	for(i = 0; i < size; i++) {
		for(j = 0; j < size; j++) {
			*((board+i*size) + j) = 0;
		}
	}
}


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
    if(numBelow + numAbove >= 3){
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
    if(numDiagUpperRight + numDiagLowerLeft >= 3) {
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
    if(numDiagUpperLeft + numDiagLowerRight >= 3) {
      return value;
    }
    return 0;
}

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

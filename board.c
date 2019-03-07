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
  printf("    ");
  for(i = 0; i < size; i++) {
    printf("%d ", i+1);
  }
  printf("\n");
	for(i = 0; i < size; i++) {
    printf("%d - ", i+1);  //print row number
		for(j = 0; j < size; j++) {
			printf("%d ", *((board+i*size) +j));
		}
	  printf("\n");
	}
}

void placeMove(int *board, int turn, int column, int size) {
  int movePlaced = 0;
  int i = size - 1;
  while(movePlaced == 0 && i >= 0) {
    if(*((board+i*size) + column) == 0) {
      *((board+i*size) + column) = 1;
      movePlaced = 1;
    }
    i--;
  }
}

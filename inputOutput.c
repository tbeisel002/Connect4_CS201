#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "inputOutput.h"
#include "board.h"

int printMenu() {
  int response;
  printf("\n\nSelect a menu choice\n");
  printf("1 - Play a player vs player game\n");
  printf("2 - Play a user vs computer game\n");
  printf("3 - View/Reset player vs player statistics\n");
  printf("4 - View/Reset user vs computer statistics\n");
  printf("5 - Exit game\n");
  printf("-->");
  scanf("%d", &response);
  while(response < 1 || response > 5) {
    printf("Please enter a valid menu choice (1-5)\n");
    printf("-->");
    scanf("%d", &response);
  }
  return response;
}

int getBoardSize() {
	int size;
	printf("Enter the length/width of the square board: ");
	scanf("%d", &size);
  while(size < 4) {
    printf("Board size can not be smaller than 4\n");
    printf("Enter the length/width of the square board: ");
  	scanf("%d", &size);
  }
	return size;
}

int * promptPlayerMove(int turnCount, int size, int *board) {
  static int arr[2];
  int col, colHeight;
  printf("\nPlayer %d's turn. Enter column number: ", turnCount);
  scanf("%d", &col);
  if(col <= size && col > 0) { // implement check col height function
    colHeight = colFull((int *)board, col - 1, size);
  }
  while((col < -1 || col > size || col == 0) || colHeight == -1) {
    if(col < -1 || col > size || col == 0) {
      printf("Column number must be between 1 and %d\n", size);
    }
    else {
      printf("That column is already full\n");
    }
    printf("Enter column number: ");
    scanf("%d", &col);
    colHeight = colFull((int *)board, col - 1, size);
    while(colHeight == -1 || (col < -1 || col > size || col == 0)) {
      if((col < -1 || col > size || col == 0)) {
        printf("Column number must be between 1 and %d\n", size);
      }
      else {
        printf("That column is already full\n");
      }
      printf("Enter column number: ");
      scanf("%d", &col);
      colHeight = colFull((int *)board, col - 1, size);
    }
  }
  arr[0] = col;
  arr[1] = colHeight;
  return arr;
}

char printPvpWins(int p1Wins, int p2Wins) {
  char response;
  printf("\nPlayer 1 has %d Wins\n", p1Wins);
  printf("Player 2 has %d Wins\n", p2Wins);
  printf("Would you like to reset win counts? (y/n)\n");
  printf("-->");
  scanf(" %c", &response);
  if(response != 'y' || response != 'n') {
      int valid = 0;
      while(valid == 0) {
        if(response == 'y' || response == 'n') {
          valid = 1;
        }
        else {
          printf("Invalid Response. Please enter y or n\n");
          printf("-->");
          scanf(" %c", &response);
        }
      }
  }
  return response;
}

char printPvcWins(int pWins, int cWins) {
  char response;
  printf("\nUser has %d Wins\n", pWins);
  printf("Computer has %d Wins\n", cWins);
  printf("Would you like to reset win counts? (y/n)\n");
  printf("-->");
  scanf(" %c", &response);
  if(response != 'y' || response != 'n') {
      int valid = 0;
      while(valid == 0) {
        if(response == 'y' || response == 'n') {
          valid = 1;
        }
        else {
          printf("Invalid Response. Please enter y or n\n");
          printf("-->");
          scanf(" %c", &response);
        }
      }
  }
  return response;
}

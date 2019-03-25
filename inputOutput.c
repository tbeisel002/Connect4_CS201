#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "inputOutput.h"
#include "board.h"

int printMenu() {
  char response[100];
  printf("\n\nSelect a menu choice\n");
  printf("1 - Play a player vs player game\n");
  printf("2 - Play a user vs computer game\n");
  printf("3 - View/Reset player vs player statistics\n");
  printf("4 - View/Reset user vs computer statistics\n");
  printf("5 - Exit game\n");
  printf("-->");
  do {
    scanf(" %s", response);
    if(verifyIntInRange(response, 1, 5) != -2) {
      break;
    }
    printf("Please enter a valid menu choice (1-5)\n");
    printf("-->");
  } while(1);
  return atoi(response);
}

int getBoardSize() {
	char size[100];
	printf("Enter the length/width of the square board: ");
  do {
  	scanf(" %s", size);
    if(verifyIntInRange(size, 4, 1000000) != -2) {
      break;
    }
    printf("Invalid input. Board size can not be smaller than 4\n");
    printf("Enter the length/width of the square board: ");
  } while(1);
	return atoi(size);
}

int * promptPlayerMove(int turnCount, int size, int *board) {
  static int arr[2];
  int colHeight, col;
  char colInput[100];
  int column;
  printf("\nPlayer %d's turn. Enter column number: ", turnCount);
  do {
    scanf(" %s", colInput);
    col = verifyIntInRange(colInput, 1, size);
    if(col != -2) {
      colHeight = colFull((int *)board, col - 1, size);
      if(colHeight != -1) {
        arr[0] = col;
        arr[1] = colHeight;
        return arr;
      }
      printf("That column is already full\n");
    }
    else if(checkForExitCode(colInput) == 1) {
      arr[0] = -1;
      arr[1] = -1;
      return arr;
    }
    else {
      printf("Column number must be between 1 and %d\n", size);
    }
    printf("Enter column number: ");
  } while(1);
  return arr;
}

char printPvpWins(int p1Wins, int p2Wins) {
  char response[100];
  printf("\nPlayer 1 has %d Wins\n", p1Wins);
  printf("Player 2 has %d Wins\n", p2Wins);
  printf("Would you like to reset win counts? (y/n)\n");
  printf("-->");
  do {
    scanf(" %s", response);
    if((int)strlen(response) == 1 && (response[0] == 'y' || response[0] == 'n')) {
      break;
    }
    printf("Invalid Response. Please enter y or n\n");
    printf("-->");
  } while(1);
  return response[0];
}

char printPvcWins(int pWins, int cWins) {
  char response[100];
  printf("\nUser has %d Wins\n", pWins);
  printf("Computer has %d Wins\n", cWins);
  printf("Would you like to reset win counts? (y/n)\n");
  printf("-->");
  do {
    scanf(" %s", response);
    if((int)strlen(response) == 1 && (response[0] == 'y' || response[0] == 'n')) {
      break;
    }
    printf("Invalid Response. Please enter y or n\n");
    printf("-->");
  } while(1);
  return response[0];
}

int verifyIntInRange(char *input, int low, int high) {
  int length = (int)strlen(input);
  if(high < 10 && length != 1) {
    return -2;
  }
  for(int i = 0; i < length; i++) {
    if(!isdigit(input[i])) {
      return -2;
    }
  }
  int intInput = atoi(input);
  if(intInput < low || intInput > high) {
    return -2;
  }
  return intInput;
}

int checkForExitCode(char *input) {
  int length = (int)strlen(input);
  if(length == 2) {
    if(input[0] == '-' && input[1] == '1') {
      return 1;
    }
  }
  return 0;
}

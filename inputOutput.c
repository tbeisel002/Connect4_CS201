/************************************************
* inputOutput.c file
* This file contains the necessary functions for obtaining input from the user.
* Every function reads in the input as a string, confirms that the input is valid,
* and then returns that input to the main method inside of main.c. If the input
* is not valid, the program will continue to prompt the user until valid input is
* given. Every string is given a size of char [100]. If the user's input is larger
* than 100, the program will inform the user that their input was invalid and
* that they entered too many characters. The program will then safely close using
* exit(1) as opposed to incurring a seg fault.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "inputOutput.h"
#include "board.h"

// Private functions
static int verifyIntInRange(char *input, int low, int high);
static int checkForExitCode(char *input);
static void checkForMaxStringLen(char *input, int size);

//Public functions
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
    scanf(" %100s", response);
    checkForMaxStringLen(response, 100);
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
  	scanf(" %100s", size);
    checkForMaxStringLen(size, 100);
    if(verifyIntInRange(size, 4, 1000000) != -2) {
      break;
    }
    printf("Invalid input. Board size can not be smaller than 4\n");
    printf("Enter the length/width of the square board: ");
  } while(1);
  if(atoi(size) >= 40) {
    char response[100];
    printf("WARNING. A Board size that large may cause display issues. ");
    printf("Would you like to change the board size? (y/n)\n");
    printf("-->");
    do {
      scanf(" %100s", response);
      checkForMaxStringLen(response, 100);
      if((int)strlen(response) == 1 && (response[0] == 'y' || response[0] == 'n')) {
        break;
      }
      printf("Invalid Response. Please enter y or n\n");
      printf("-->");
    } while(1);
    if(response[0] == 'y') {
      return getBoardSize();
    }
  }
	return atoi(size);
}

int * promptPlayerMove(int turnCount, int size, int *board) {
  static int arr[2];
  int colHeight, col;
  char colInput[100];
  int column;
  printf("\nPlayer %d's turn. Enter column number: ", turnCount);
  do {
    scanf(" %100s", colInput);
    checkForMaxStringLen(colInput, 100);
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
      char response[100];
      printf("WARNING. Your game will not be saved. ");
      printf("Would you still like to return to the main menu? (y/n)\n");
      printf("-->");
      do {
        scanf(" %100s", response);
        checkForMaxStringLen(response, 100);
        if((int)strlen(response) == 1 && (response[0] == 'y' || response[0] == 'n')) {
          break;
        }
        printf("Invalid Response. Please enter y or n\n");
        printf("-->");
      } while(1);
      if(response[0] == 'n') {
        return promptPlayerMove(turnCount, size, board);
      }
      else {
        arr[0] = -1;
        arr[1] = -1;
        return arr;
      }
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
  if(p1Wins == 1) {
    printf("\nPlayer 1 has %d Win\n", p1Wins);
  }
  else {
    printf("\nPlayer 1 has %d Wins\n", p1Wins);
  }
  if(p2Wins == 1) {
    printf("Player 2 has %d Win\n", p2Wins);
  }
  else {
    printf("Player 2 has %d Wins\n", p2Wins);
  }
  printf("Would you like to reset win counts? (y/n)\n");
  printf("-->");
  do {
    scanf(" %100s", response);
    checkForMaxStringLen(response, 100);
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
  if(pWins == 1) {
    printf("\nUser has %d Win\n", pWins);
  }
  else {
    printf("\nUser has %d Wins\n", pWins);
  }
  if(cWins == 1) {
    printf("Computer has %d Win\n", cWins);
  }
  else {
    printf("Computer has %d Wins\n", cWins);
  }
  printf("Would you like to reset win counts? (y/n)\n");
  printf("-->");
  do {
    scanf(" %100s", response);
    checkForMaxStringLen(response, 100);
    if((int)strlen(response) == 1 && (response[0] == 'y' || response[0] == 'n')) {
      break;
    }
    printf("Invalid Response. Please enter y or n\n");
    printf("-->");
  } while(1);
  return response[0];
}

static int verifyIntInRange(char *input, int low, int high) {
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

static int checkForExitCode(char *input) {
  int length = (int)strlen(input);
  if(length == 2) {
    if(input[0] == '-' && input[1] == '1') {
      return 1;
    }
  }
  return 0;
}

static void checkForMaxStringLen(char *input, int size) {
  if(strlen(input) == size) {
    printf("Invalid input, too many characters entered. Program Closing.\n");
    exit(1);
  }
}

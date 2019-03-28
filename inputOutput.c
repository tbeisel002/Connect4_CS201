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

/*
* return - int 1-5 of the menu choice
*****
*****
* printMenu prints the menu, makes sure the users choice is valid, and then returns
* the users choice
*/
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

/*
* return - int of the user input board size
*****
*****
* getBoardSize prompts the user to enter the board size, ensures that the users
* input is valid, and then returns the users input
*/
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

/*
* turnCount - keeps track of whose turn it is
* size - the size of the board
* *board - the 2d array repesenting the connect 4 board
* return - array in the format [column][columnHeight]
*        - columnHeight is calcuated and is returned to avoid calcuating it again
*****
*****
* promptPlayerMove prompts the user to select a column to play in. The function
* validates that the input is an int in the range of columns on the board and
* that the selected column is not already full. A user input of -1 will return to
* the main menu. The user will be prompted to make sure that this is what he/she
* wants to do.
*/
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

/*
* p1Wins - the amount of wins player 1 has
* p2Wins - the amount of wins player 2 has
* return - char of 'y' or 'n' on if the user would like to reset these numbers
*****
*****
* printPvpWins prints the number of wins for each player. The function then prompts
* user to ask if they'd like these numbers to be reset. The function validates the
* user's input and then returns it.
*/
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

/*
* pWins - the amount of wins player 1 has
* cWins - the amount of wins the cpu has
* return - char of 'y' or 'n' on if the user would like to reset these numbers
*****
*****
* printPvpWins prints the number of wins for the player and cpu The function then prompts
* user to ask if they'd like these numbers to be reset. The function validates the
* user's input and then returns it.
*/
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

/*     PRIVATE
* *input - the string of the user input
* low - the low end of the range of acceptable numbers for the input to be in
* high - the high of the range of acceptable number for the input to be in
* return - -2 if the input is not a number in the acceptable range
         - the number if it is in the acceptable range
         - note, -2 is used to avoid confusion with the exit code of -1
*****
*****
* verifyIntInRange takes a string and verifies that the string is an integer in
* the given range. The integer is returned if so. If not, -2 is returned.
*/
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

/*     PRIVATE
* *input - the string of the user input
* return - 1 if the user entered the exit code (-1), 0 otherwise
*****
*****
* checkForExitCode checks to see if the input was the exit code. If it was it
* returns 1 to represent True, 0 to represent false.
* - note - when I worked on my project, I didn't realize we were allowed to use
*          bool.h. That is why you see 1 and 0 used to represent True and False
*          throughout my code.
*/
static int checkForExitCode(char *input) {
  int length = (int)strlen(input);
  if(length == 2) {
    if(input[0] == '-' && input[1] == '1') {
      return 1;
    }
  }
  return 0;
}

/*     PRIVATE
* *input - the string of the user input
* size - the max size of the string
*****
*****
* checkForMaxStringLen checks to see if the max size that was allocated for the
* users input was filled. If it was, the function closes the program instead of
* causing a seg fault.
*/
static void checkForMaxStringLen(char *input, int size) {
  if(strlen(input) == size) {
    printf("Invalid input, too many characters entered. Program Closing.\n");
    exit(1);
  }
}

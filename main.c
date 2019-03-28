/************************************************
* Main.c file
* This file contains the main method for the program. The body of the main method
* consists of a while loop that goes in and out of the 4 menu choices, calling
* the needed external functions for each one. The while loop exits once menu
* choice 5 is selected and the program is terminated.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "board.h"
#include "inputOutput.h"
#include "bot.h"

int main(void) {
	printf("Welcome to Connect 4!");
	char response;
	int player1Wins = 0;
	int player2Wins = 0;
	int cpuWins = 0;
	int userWins = 0;
	int i;
	int menuChoice = printMenu();
	while(menuChoice != 5) { // while the user has not selected menu choice 5 (exit)
		if(menuChoice <= 2) { // if the user has selected to play a game
			int boardSize = getBoardSize();
			int * board;
    	board = (int*)malloc(sizeof(int)*boardSize*boardSize);
			printf("\nEnter -1 at any point to return to main menu. Your game will not be saved\n");
			createBoard((int *)board, boardSize);
			printBoard((int *)board, boardSize);
			int turnCount = 1;
			int gameOver = 0;
			int numMoves = 0;

			if(menuChoice == 1) { // player vs player
				while(gameOver == 0) {
					int *arr = promptPlayerMove(turnCount, boardSize, (int *)board);
					numMoves++;
					if(*(arr) == -1) { // if player entered exit code
						gameOver = 1;
						break;
					}
					placeMove((int *)board, turnCount, *(arr) - 1, boardSize);
					printBoard((int *)board, boardSize);
					gameOver = checkGameState((int *)board, boardSize, (*(arr)) - 1, *(arr+1));
					if(numMoves >= boardSize * boardSize) {
						printf("The game is over... you tied.\n\n");
						userWins++;
						break;
					}
					if(gameOver != 0) {
						printf("Congrats Player %d, You Won!!!\n\n", turnCount);
						if(turnCount == 1) {
							player1Wins++;
						}
						else {
							player2Wins++;
						}
					}
					if(turnCount == 1) {
						turnCount++;
					}
					else {
						turnCount--;
					}
				}
			}
			else { // player vs computer
				int columnOrder[boardSize]; // create the middle-out order of columns.
				for(i = 0; i < boardSize; i++) { // see bot.c for description of why this is useful
					columnOrder[i] = boardSize/2 + (1-2*(i%2)) *(i+1)/2;
				}
				while(gameOver == 0) {
					int *arr = promptPlayerMove(turnCount, boardSize, (int *)board);
					int userColPlayed = *(arr) - 1 ;
					if(*(arr) == -1) { // if player entered exit code
						gameOver = 1;
						break;
					}
					placeMove((int *)board, 1, userColPlayed, boardSize);
					printBoard((int *)board, boardSize);
					numMoves++;
					gameOver = checkGameState((int *)board, boardSize, userColPlayed, *(arr+1));
					if(gameOver != 0) {
						printf("Congrats Player 1, You Won!!!\n\n");
						userWins++;
						break;
					}
					if(numMoves >= boardSize * boardSize) {
						printf("The game is over... you tied.\n\n");
						userWins++;
						break;
					}
					// ***** AI SECTION ******
					int *aiMove = minAlg((int *)board, boardSize, 0, numMoves, *(arr) - 1,
					*(arr+1), -1000000, 1000000, columnOrder);
					placeMove((int *)board, 2, *(aiMove), boardSize);
					numMoves++;
					printf("\nThe computer played column %d\n", *(aiMove) + 1);
					printBoard((int *)board, boardSize);
					int cpuHeight = getPrevHeight((int *)board, boardSize, *aiMove);
					gameOver = checkGameState((int *)board, boardSize, *(aiMove), cpuHeight);
					if(gameOver == 2) {
						printf("The Computer Won, Better Luck Next Time.\n\n");
						cpuWins++;
						break;
					}
					if(numMoves >= boardSize * boardSize) {
						printf("The game is over... you tied.\n\n");
						userWins++;
						break;
					}
				}
			}
			free(board);
		}
		else if(menuChoice == 3) { // view player vs player serie
			response = printPvpWins(player1Wins, player2Wins);
			if(response == 'y') {
				player1Wins = 0;
				player2Wins = 0;
			}
		}
		else { // view player vs computer series
			response = printPvcWins(userWins, cpuWins);
			if(response == 'y') {
				userWins = 0;
				cpuWins = 0;
			}
		}
		menuChoice = printMenu();
	}
}

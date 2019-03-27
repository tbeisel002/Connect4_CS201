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
	while(menuChoice != 5) {
		if(menuChoice <= 2) {
			int boardSize = getBoardSize();
			//int board [boardSize][boardSize];
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
					if(*(arr) == -1) {
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
				int columnOrder[boardSize];
				//int columnOrder[20];
				//if(boardSize <= 20) {
				for(i = 0; i < boardSize; i++) {
					columnOrder[i] = boardSize/2 + (1-2*(i%2)) *(i+1)/2;
				}
				//}
				while(gameOver == 0) {
					int *arr = promptPlayerMove(turnCount, boardSize, (int *)board);
					if(*(arr) == -1) {
						gameOver = 1;
						break;
					}
					placeMove((int *)board, 1, *(arr) - 1, boardSize);
					printBoard((int *)board, boardSize);
					numMoves++;
					gameOver = checkGameState((int *)board, boardSize, (*(arr)) - 1, *(arr+1));
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
					//if(boardSize > 20) { // only search cols +- 10 of where user played
						//for(i = 0; i < 20; i++) { // fixes run speed for boards n > 20
							//columnOrder[i] = ((*(arr) - 1) + 10)/2 + (1-2*(i%2)) *(i+1)/2;
						//}
						//for(i = 0; i < 20; i++) { // fixes run speed for boards n > 20
							//printf("%d\n", columnOrder[i]);
						//}
					//}
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
			free(board);    // this frees the rows
			menuChoice = printMenu();
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

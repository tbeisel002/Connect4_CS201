#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "board.h"
#include "inputOutput.h"


int main(void) {
	int gameType = getGameType();
	int boardSize = getBoardSize();
	int board [boardSize][boardSize];

	createBoard((int *)board, boardSize);
	printBoard((int *)board, boardSize);

	int turnCount = 1;
	int col = promptPlayerMove(turnCount);
	placeMove((int *)board, turnCount, col-1, boardSize);
	printBoard((int *)board, boardSize);
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "inputOutput.h"

int getGameType() {
  int answer;
  printf("Welcome to Connect 4\n");
  printf("Enter 0 for player vs player or 1 for player vs cpu: ");
  scanf("%d", &answer);
  return answer;
}
int getBoardSize() {
	int size;
	printf("Enter the length/width of the square board: ");
	scanf("%d", &size);
	return size;
}

int promptPlayerMove(int turnCount) {
  int col;
  printf("Player %d's turn. Enter column number: ", turnCount);
  scanf("%d", &col);
  return col;
}

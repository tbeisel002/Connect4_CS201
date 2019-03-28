all : main.c board.c inputOutput.c bot.c
	gcc -std=c11 -Wall -o connect4 main.c board.c inputOutput.c bot.c

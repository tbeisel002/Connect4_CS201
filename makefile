all : main.c board.c inputOutput.c bot.c
	gcc -o connect4 main.c board.c inputOutput.c bot.c

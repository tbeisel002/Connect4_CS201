all : main.c board.c inputOutput.c position.c
	gcc -o connect4 main.c board.c inputOutput.c position.c bot.c

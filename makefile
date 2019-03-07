all : main.c board.c inputOutput.c
	gcc -o connect4 main.c board.c inputOutput.c

# Connect4_CS201

This is my cs 201 portfolio project. When running the program, the menu is very simple and easy to understand. You can play a user vs user game, play a user vs cpu game, or view/reset the series stats for either of these options. The ai uses an alpha beta variant of the minimax algorithm to determine the next best move. For a much more detailed description of the algorithm, see the header comments in 'bot.c'.  

## Running the program

Once you download the repo, use make to build the project and the executable is named 'connect4'. So inside of the project folder type 'make' and then './connect4' and the program will start!

## Video Link

Update this with the video link once I record the video.

## Additional Notes About Using the Program

- User input is capped at 100 characters. If a user enters more than 100 characters, the program will inform the user and gracefully exit to avoid a segmentation fault. <br>
- Every function is commented thoroughly, so for descriptions of the dfs algorithm used, the end game calculator, or any other function, look at the source code. <br>
- When in a game, entering -1 for your turn will return you to the main menu without saving your game. The program will prompt you to confirm that this is what you would like to do. <br>

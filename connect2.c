#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
char name1[20];
char name2[20];
char *currentPlayer;
int height = 6;
int width = 7;
int **board;
char inputValue;		//Value input by the player
int gameState = 0;		//When gameState = 1, game ends
int fullColumn = 0;
int nextPlayer = 1;		//Indicator for which players turn it is

/**
Helper function that creates the board.
*/
int createBoard(){

	board = (int **)malloc(width*sizeof(int *));
	for(int w = 0; w < width; w++)
		board[w] = (int *)malloc(height*sizeof(int));
	for (int w = 0; w < width; w++) {
 		for (int h = 0; h < height; h++) {
    			board[w][h] = 0;
   		}
   	}

  return 0;
}
/**
Helper function that displays the board.
*/
int displayBoard(){

	printf("\t\033[1;37m    A   B   C   D   E   F   G");
	for(int h = 0;h<height;h++){
   		printf("\n\t  \033[01;33m-----------------------------\033[0m\n\t  ");
   	for(int w = 0; w < width;w++){
   		if(w == 0)
   			printf("\033[01;33m| \033[0m");
   		if(board[w][h] == 1)											//Player 1 color is blue
   			printf("\033[1;34m%d \033[01;33m| \033[0m",board[w][h]);
   		else if(board[w][h] == 2)										//Player 2 color is red
   			printf("\033[1;31m%d \033[01;33m| \033[0m",board[w][h]);
   		else															//Board structure is yellow
   			printf("\033[0;37m%d \033[01;33m| \033[0m",board[w][h]);
   		
   		if(w == 6 && h == 5)
   			printf("\n\t  \033[01;33m-----------------------------\033[0m");
   		}
   	}
   	return 0;
}

/**
/Funtion that sets up the game
*/
int initialization(){
	
	printf("Setting up the game...\n");
	printf("Player One Name: \n");
	scanf("%s",name1);
	printf("Player Two Name: \n");
	scanf("%s",name2);

	createBoard();

	return 0;
}

/*
/Function that ends the game and all processes
*/
int teardown(){
	
	printf("\t       \033[0;37mDestroying the game...\n\n\n");
	free(board);
	return 0;
}

/**
/Function that accepts the users input and returns a char value
*/
char acceptInput(){

	if (nextPlayer == 1)			//Checks which players turn it is.
		currentPlayer = name1;
	else
		currentPlayer = name2;

	if(inputValue == '\0')			//Shows the empty board for the first move.
		displayBoard();

		printf("\n\t\t      \033[0;37m%s\n\t       Choose a column A-G\n\t         Enter Q to quit\n\n",currentPlayer);
		scanf(" %c",&inputValue);
		inputValue = toupper(inputValue);

		if(inputValue < 65 || inputValue > 71){		//Checks if input value is between A and G.

			if(inputValue == 81){}		//If inpue value is Q.
				
			else{
				printf("\t\t  Not in range\n");		//If input is out of range, runs acceptInput again.
				acceptInput();
		}
	}
	return inputValue;
}

/**
/Function that does calculations to update the world based on the input value from acceptInput()
*/
int updateWorld(char inputValue){

	int player;
	if(currentPlayer == name1)
		player = 1;
	else
		player = 2;

	if(inputValue == 81)						//Checks if player Quit
		gameState = 1;

	else{
		int discPlacement = inputValue - 65;	//Uses ASCII value to determine what slot was chosen

		if(board[discPlacement][0] != 0){		//If column is full, game ends	
			gameState = 1;
			fullColumn = 1;
		}
		else{
			for(int h = 5; h >=-1; h--){				//Places disc in empty slot of selected column
				if(board[discPlacement][h] == 0){
					board[discPlacement][h] = player;
					break;
				}
			}
		}
	}

//Checks for Connect4 Vertically
	for (int w = 0; w < width; w++) {
 		for (int h = 0; h < height; h++) {

 			if(board[w][h] != 0 && board[w][h] == board[w][h+1])
 				if(board[w][h+1] == board[w][h+2])
 					if(board[w][h+2] == board[w][h+3])
 						gameState = 1;
		}
	}

//Checks for Connect4 Horizontally
	for (int h = 0; h < height; h++) {
 		for (int w = 0; w < width; w++) {
 		
 			if(w < 4 && board[w][h] != 0 && board[w][h] == board[w+1][h]) 				
 				if(board[w+1][h] == board[w+2][h])
 					if(board[w+2][h] == board[w+3][h])
 						gameState = 1;
 		}
	}
	

//Checks for Connect4 Diagonally to the bottom right direction
	for (int h = 0; h < height; h++) {
 		for (int w = 0; w < width; w++) {
 			if(w < 4 && h < 3 && board[w][h] != 0 && board[w][h] == board[w+1][h+1])
 				if(board[w+1][h+1] == board[w+2][h+2])
 					if(board[w+2][h+2] == board[w+3][h+3])
 						gameState = 1;
 		}
 	}

//Checks for Connect4 Diagonally to the bottom left direction
 	for (int h = 0; h < height; h++) {
 		for (int w = 0; w < width; w++) {
 			if(w > 2 && h < 3 && board[w][h] != 0 && board[w][h] == board[w-1][h+1])
 				if(board[w-1][h+1] == board[w-2][h+2])
 					if(board[w-2][h+2] == board[w-3][h+3])
 						gameState = 1;
 		}
 	}
 	return 0;
 }

/**
/Function that displays the results from updateWorld()
*/
int displayWorld(){

	displayBoard();
	if(gameState == 1 && inputValue != 81 && fullColumn == 0)
		printf("\n\t\t    \033[0;37m%s Wins!\n",currentPlayer);
	else if(inputValue == 81 || fullColumn == 1)
		printf("\n\t\t  \033[0;37mQuitting Game\n");

	
	return 0;
}

/**
/Main function to run all other functions and create game loop
*/
int main(int argc, char *argv[]){

	initialization();

	while(gameState == 0){

		acceptInput();
		updateWorld(inputValue);
		displayWorld();
		nextPlayer *= -1;
	};

	teardown();
	return 0;
}

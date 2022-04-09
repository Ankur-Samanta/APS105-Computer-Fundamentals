/*
 * File:        project_reversi_skeleton.c
 * Author:      APS105H1 Teaching Team
 * Modified by: Ankur Samanta
 *
 * Date: March 25 2021
 */

#include "project_reversi_skeleton.h" // DO NOT modify this line
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

//Note: You may want to add more function declarations here
//I have placed function declarations in progressive order between the pre-defined functions in the skeleton code. 

// ========= Function implementation ==========
/*
 * Function:  printBoard 
 * --------------------
 * Print the whole board to the terminal window.
 */
void printBoard(char board[][26], int n) {
    printf("  ");
    for(int iterator = 0; iterator < n; iterator ++){
        char a = (char)('a' + iterator);
        printf("%c",  a);
	}
	printf("\n");
	for(int rowIterator = 0; rowIterator < n; rowIterator ++){
		char a = (char)('a' + rowIterator);
        printf("%c ",  a);
		for(int colIterator = 0; colIterator < n; colIterator ++){
			printf("%c", board[rowIterator][colIterator]);
		}
		printf("\n");
	}
}

//below function initializes the board with U, W, and B values
void initializeBoard(char board[][26], int n) {
    for(int rowIterator = 0; rowIterator < n; rowIterator ++){
		for(int colIterator = 0; colIterator < n; colIterator ++){
			board[rowIterator][colIterator] = 'U';
            if ((rowIterator == (n / 2) && colIterator == n / 2) || (rowIterator == (n / 2 - 1) && colIterator == (n / 2 - 1))) {
                board[rowIterator][colIterator] = 'W';
            }
            if ((rowIterator == (n / 2) && colIterator == (n / 2 - 1)) || (rowIterator == (n / 2 - 1) && colIterator == (n / 2))) {
                board[rowIterator][colIterator] = 'B';
            }
		}
	}
}

//below function configures the board
void configureBoard(char board[][26], int n){
	char boardConfig[3];
    printf("Enter board configuration:\n");
	scanf("%s", boardConfig);
	while(strcmp(boardConfig, "!!!") != 0){
        char configColour = boardConfig[0];
        int configRow = boardConfig[1] - 'a';
		int configCol = boardConfig[2] - 'a';
		board[configRow][configCol] = configColour;
		scanf("%s", boardConfig);
	}
}

/*
 * Function:  positionInBounds 
 * --------------------
 * Checks whether the specified (row, col) lies within the board dimensions.
 */
bool positionInBounds(int n, int row, int col) {
    if(col >= 0 && row >= 0 && col < n && row < n ){
        return true;
    }
    return false;  
}

/*
 * Function:  checkLegalInDirection 
 * --------------------
 * Checks whether (row, col) is a legal position for a tile of colour by “looking” in the direction 
 * specified by deltaRow and deltaCol.
 */
bool checkLegalInDirection(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol) {
    int rowTemp, colTemp, iterator = 0;
	rowTemp = row, colTemp = col;
	while(positionInBounds(n, rowTemp,colTemp)) {
		if(board[rowTemp][colTemp] == colour && iterator > 1) {
			return true;
        }
        if((board[rowTemp][colTemp] != 'U' && iterator == 0) || (board[rowTemp][colTemp] == 'U' && iterator != 0) || (board[rowTemp][colTemp] == colour && iterator == 1)) {
			return false;
        }
		rowTemp += deltaRow, colTemp += deltaCol, iterator += 1;
    }
	return false;            
}

//below function checks legality of move in all 8 directions
bool checkFullDirectionalLegality(char board[][26], int n, int row, int col, char colour) {
    for (int rowIterator = -1; rowIterator <= 1; rowIterator ++) {
        for (int colIterator = -1; colIterator <= 1; colIterator ++) {
            if(!(rowIterator == 0 && colIterator == 0) && checkLegalInDirection(board, n, row, col, colour, rowIterator, colIterator)) {
                return true;
            }
        }
    }
    return false;
}

//below function prints possible moves
void printAvailableMoves(char board[][26], int n, char colour) {
    for (int rowIterator = 0; rowIterator < n; rowIterator ++) {
        for (int colIterator = 0; colIterator < n; colIterator ++) {
            if (checkFullDirectionalLegality(board, n, rowIterator, colIterator, colour)) {
                //printf("%e", checkFullDirectionalLegality(board, n, rowIterator, colIterator, colour));
                char y = (char)(rowIterator + 'a'); 
                char x = (char)(colIterator + 'a');
                printf("%c%c\n", y, x);
            }
        }
    }
}

/*
 * Function:  makeMove 
 * --------------------
 * The player "turn" makes a move at (row, col).
 * Note: This function MUST NOT change board, only row and col can be changed to reflect the move.
 */
int makeMove(const char board[26][26], int n, char turn, int *row, int *col) {
    (void)board;
    (void)n;
    (void)turn;
    (void)row;
    (void)col;
    return 0;
}

//below function defines how to flip the colour of the tile
void flipTile(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol) {
    int rowTemp = row, colTemp = col; 
    while(board[rowTemp][colTemp] != colour) { 
        board[rowTemp][colTemp] = colour;
        rowTemp += deltaRow, colTemp += deltaCol;
    }
}

//below function flips tile if move is valid
void flipTileIfValid(char board[][26], int n, int row, int col, char colour) {
    for (int rowIterator = -1; rowIterator <= 1; rowIterator ++) {
        for (int colIterator = -1; colIterator <= 1; colIterator ++) {
            if(!(rowIterator == 0 && colIterator == 0) && checkLegalInDirection(board, n, row, col, colour, rowIterator, colIterator)) {
                flipTile(board, n, row, col, colour, rowIterator, colIterator);
            }
        }
    }
}

#ifndef COMPETE_MODE // DO NOT DELETE THIS LINE
int main(void) {
    // Complete your main function here
    //initialize variable and character arrays
    int n;
    char board[26][26], nextMove[3];

    //get initial input on board dimensions
    printf("Enter the board dimension: ");
    scanf("%i", &n);

    //initialize and configure the board
    initializeBoard(board, n);
    printBoard(board, n);
    configureBoard(board, n);
    printBoard(board, n);

    //print the available moves for W and B
    printf("Available moves for W:\n");
    printAvailableMoves(board, n, 'W');
    printf("Available moves for B:\n");
    printAvailableMoves(board, n, 'B');

    //get user input for the next move in a 3x1 array, including information about the colour, row, and column of the move
    printf("Enter a move:\n");
    scanf("%s", nextMove);

    //assign values for the new colour, row, and column of the next move as defined from the previous user input
    char nextColour = nextMove[0];
    int nextRow = (int)(nextMove[1] - 'a');
    int nextCol = (int)(nextMove[2] - 'a');	

    //if the move is legal, print validity and switch the colour of the tiles that need to be switched, or else print invalidity of move
    if(checkFullDirectionalLegality(board, n, nextRow, nextCol, nextColour)) {
        printf("Valid move.\n");
        flipTileIfValid(board, n, nextRow, nextCol, nextColour);
    }
    else {
        printf("Invalid move.\n");
    }
    printBoard(board, n);

    return 0;
}
#endif // DO NOT DELETE THIS LINE
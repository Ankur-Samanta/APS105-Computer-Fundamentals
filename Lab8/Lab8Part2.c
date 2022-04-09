/*
 * File:        project_reversi_skeleton.c
 * Author:      APS105H1 Teaching Team
 * Modified by: Ankur Samanta
 * Date: April 8 2021
 */

//#include "project_reversi_skeleton.h" // DO NOT modify this line
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

// ========= Function implementation ==========
//Print the whole board to the terminal window.
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

//Checks whether the specified (row, col) lies within the board dimensions.
bool positionInBounds(int n, int row, int col) {
    if(col >= 0 && row >= 0 && col < n && row < n ){
        return true;
    }
    return false;  
}

//Checks whether (row, col) is a legal position for a tile of colour by “looking” in the direction specified by deltaRow and deltaCol.
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

//below function checks whether a move is possible
bool isMoveAvailable(char board[][26], int n, char colour) {
    for (int rowIterator = 0; rowIterator < n; rowIterator ++) {
        for (int colIterator = 0; colIterator < n; colIterator ++) {
            if (checkFullDirectionalLegality(board, n, rowIterator, colIterator, colour) == true) {
                return true;
            }
        }
    }
    return false;
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
            board[row][col] = 'U';
            if(!(rowIterator == 0 && colIterator == 0) && checkLegalInDirection(board, n, row, col, colour, rowIterator, colIterator)) {
                flipTile(board, n, row, col, colour, rowIterator, colIterator);
            }
            board[row][col] = colour;
        }
    }
}

/*
 * Function:  makeMove 
 * --------------------
 * The player "turn" makes a move at (row, col).
 * Note: This function MUST NOT change board, only row and col can be changed to reflect the move.
 */

//evaluates move and scores it 
int evaluateMove(char board[][26], int n, int row, int col, char colour) {
    int score = 0;
    for (int rowIterator = -1; rowIterator <= 1; rowIterator ++) {
        for (int colIterator = -1; colIterator <= 1; colIterator ++) {
            if(!(rowIterator == 0 && colIterator == 0) && checkLegalInDirection(board, n, row, col, colour, rowIterator, colIterator)) {
                int tempRowVal = row + rowIterator, tempColVal = col + colIterator;
                while(board[tempRowVal][tempColVal] != colour) {
                    tempRowVal += rowIterator; tempColVal += colIterator; score ++;
                }
            }
        }
    }
    return score;
}

//makes move
int makeMove(const char board[26][26], int n, char turn, int *row, int *col) {
    int highestScore = 0, highestScoreRow, highestScoreCol; //initialize integer values for the highest score, and corresponding row/col vals
    char hypotheticalBoard[26][26]; //use a duplicate, hypothetical board to check out score based on potential moves
    for(int rowIterator = 0; rowIterator < n; rowIterator ++) {
        for(int colIterator = 0; colIterator < n; colIterator ++) {
            hypotheticalBoard[rowIterator][colIterator] = board[rowIterator][colIterator]; //copy over the real values to the hypothetical board
        }
    }
    for(int rowIterator = 0; rowIterator < n; rowIterator ++) {
        for(int colIterator = 0; colIterator < n; colIterator ++) {
            if(checkFullDirectionalLegality(hypotheticalBoard, n, rowIterator, colIterator, turn)){
                int moveScore = evaluateMove(hypotheticalBoard, n, rowIterator, colIterator, turn);
                if(moveScore == highestScore && highestScore > 0) {
                    if(rowIterator == highestScoreRow && colIterator < highestScoreCol) {highestScoreRow = rowIterator; highestScoreCol = colIterator;}
                    else if(rowIterator < highestScoreRow) {highestScoreRow = rowIterator; highestScoreCol = colIterator;}
                }
                else if(moveScore > highestScore) {
                    highestScore = moveScore;
                    highestScoreRow = rowIterator; highestScoreCol = colIterator;
                }
            }
        }
    }
    for(int rowIterator = 1; rowIterator < n - 1; rowIterator ++) {
        for(int colIterator = 1; colIterator < n - 1; colIterator ++) {
            if(checkFullDirectionalLegality(hypotheticalBoard, n, rowIterator, colIterator, turn)){
                int moveScore = evaluateMove(hypotheticalBoard, n, rowIterator, colIterator, turn);
                if(moveScore == highestScore && highestScore > 0) {
                    if(rowIterator == highestScoreRow && colIterator < highestScoreCol) {highestScoreRow = rowIterator; highestScoreCol = colIterator;}
                    else if(rowIterator < highestScoreRow) {highestScoreRow = rowIterator; highestScoreCol = colIterator;}
                }
                else if(moveScore > highestScore) {
                    highestScore = moveScore;
                    highestScoreRow = rowIterator; highestScoreCol = colIterator;
                }
            }
        }
    }
    for(int rowIterator = 2; rowIterator < n - 2; rowIterator ++) {
        for(int colIterator = 2; colIterator < n - 2; colIterator ++) {
            if(checkFullDirectionalLegality(hypotheticalBoard, n, rowIterator, colIterator, turn)){
                int moveScore = evaluateMove(hypotheticalBoard, n, rowIterator, colIterator, turn);
                if(moveScore == highestScore && highestScore > 0) {
                    if(rowIterator == highestScoreRow && colIterator < highestScoreCol) {highestScoreRow = rowIterator; highestScoreCol = colIterator;}
                    else if(rowIterator < highestScoreRow) {highestScoreRow = rowIterator; highestScoreCol = colIterator;}
                }
                else if(moveScore > highestScore) {
                    highestScore = moveScore;
                    highestScoreRow = rowIterator; highestScoreCol = colIterator;
                }
            }
        }
    }
    for(int rowIterator = 2; rowIterator < n - 2; rowIterator ++) {
        for(int colIterator = 0; colIterator < n - 0; colIterator ++) {
            if(checkFullDirectionalLegality(hypotheticalBoard, n, rowIterator, colIterator, turn)){
                int moveScore = evaluateMove(hypotheticalBoard, n, rowIterator, colIterator, turn);
                if(moveScore == highestScore && highestScore > 0) {
                    if(rowIterator == highestScoreRow && colIterator < highestScoreCol) {highestScoreRow = rowIterator; highestScoreCol = colIterator;}
                    else if(rowIterator < highestScoreRow) {highestScoreRow = rowIterator; highestScoreCol = colIterator;}
                }
                else if(moveScore > highestScore) {
                    highestScore = moveScore;
                    highestScoreRow = rowIterator; highestScoreCol = colIterator;
                }
            }
        }
    }    
    for(int rowIterator = 0; rowIterator < n - 0; rowIterator ++) {
        for(int colIterator = 2; colIterator < n - 2; colIterator ++) {
            if(checkFullDirectionalLegality(hypotheticalBoard, n, rowIterator, colIterator, turn)){
                int moveScore = evaluateMove(hypotheticalBoard, n, rowIterator, colIterator, turn);
                if(moveScore == highestScore && highestScore > 0) {
                    if(rowIterator == highestScoreRow && colIterator < highestScoreCol) {highestScoreRow = rowIterator; highestScoreCol = colIterator;}
                    else if(rowIterator < highestScoreRow) {highestScoreRow = rowIterator; highestScoreCol = colIterator;}
                }
                else if(moveScore > highestScore) {
                    highestScore = moveScore;
                    highestScoreRow = rowIterator; highestScoreCol = colIterator;
                }
            }
        }
    }
    for(int rowIterator = 2; rowIterator < n - 2; rowIterator ++) {
        for(int colIterator = 0; colIterator < n - 0; colIterator += n - 1) {
            if(checkFullDirectionalLegality(hypotheticalBoard, n, rowIterator, colIterator, turn)){
                int moveScore = evaluateMove(hypotheticalBoard, n, rowIterator, colIterator, turn);
                if(moveScore == highestScore && highestScore > 0) {
                    if(rowIterator == highestScoreRow && colIterator < highestScoreCol) {highestScoreRow = rowIterator; highestScoreCol = colIterator;}
                    else if(rowIterator < highestScoreRow) {highestScoreRow = rowIterator; highestScoreCol = colIterator;}
                }
                else if(moveScore > highestScore) {
                    highestScore = moveScore;
                    highestScoreRow = rowIterator; highestScoreCol = colIterator;
                }
            }
        }
    }    
    for(int rowIterator = 0; rowIterator < n - 0; rowIterator += n - 1) {
        for(int colIterator = 2; colIterator < n - 2; colIterator ++) {
            if(checkFullDirectionalLegality(hypotheticalBoard, n, rowIterator, colIterator, turn)){
                int moveScore = evaluateMove(hypotheticalBoard, n, rowIterator, colIterator, turn);
                if(moveScore == highestScore && highestScore > 0) {
                    if(rowIterator == highestScoreRow && colIterator < highestScoreCol) {highestScoreRow = rowIterator; highestScoreCol = colIterator;}
                    else if(rowIterator < highestScoreRow) {highestScoreRow = rowIterator; highestScoreCol = colIterator;}
                }
                else if(moveScore > highestScore) {
                    highestScore = moveScore;
                    highestScoreRow = rowIterator; highestScoreCol = colIterator;
                }
            }
        }
    }    
    for(int rowIterator = 1; rowIterator < n - 1; rowIterator ++) {
        for(int colIterator = 0; colIterator < n; colIterator ++) {
            if(checkFullDirectionalLegality(hypotheticalBoard, n, rowIterator, colIterator, turn)){
                int moveScore = evaluateMove(hypotheticalBoard, n, rowIterator, colIterator, turn);
                if(moveScore == highestScore && highestScore > 0) {
                    if(rowIterator == highestScoreRow && colIterator < highestScoreCol) {highestScoreRow = rowIterator; highestScoreCol = colIterator;}
                    else if(rowIterator < highestScoreRow) {highestScoreRow = rowIterator; highestScoreCol = colIterator;}
                }
                else if(moveScore > highestScore) {
                    highestScore = moveScore;
                    highestScoreRow = rowIterator; highestScoreCol = colIterator;
                }
            }
        }
    }
    for(int rowIterator = 0; rowIterator < n; rowIterator ++) {
        for(int colIterator = 1; colIterator < n - 1; colIterator ++) {
            if(checkFullDirectionalLegality(hypotheticalBoard, n, rowIterator, colIterator, turn)){
                int moveScore = evaluateMove(hypotheticalBoard, n, rowIterator, colIterator, turn);
                if(moveScore == highestScore && highestScore > 0) {
                    if(rowIterator == highestScoreRow && colIterator < highestScoreCol) {highestScoreRow = rowIterator; highestScoreCol = colIterator;}
                    else if(rowIterator < highestScoreRow) {highestScoreRow = rowIterator; highestScoreCol = colIterator;}
                }
                else if(moveScore > highestScore) {
                    highestScore = moveScore;
                    highestScoreRow = rowIterator; highestScoreCol = colIterator;
                }
            }
        }
    }
    for(int rowIterator = 2; rowIterator < n - 2; rowIterator ++) {
        for(int colIterator = 1; colIterator < n - 3; colIterator ++) {
            if(checkFullDirectionalLegality(hypotheticalBoard, n, rowIterator, colIterator, turn)){
                int moveScore = evaluateMove(hypotheticalBoard, n, rowIterator, colIterator, turn);
                if(moveScore == highestScore && highestScore > 0) {
                    if(rowIterator == highestScoreRow && colIterator < highestScoreCol) {highestScoreRow = rowIterator; highestScoreCol = colIterator;}
                    else if(rowIterator < highestScoreRow) {highestScoreRow = rowIterator; highestScoreCol = colIterator;}
                }
                else if(moveScore > highestScore) {
                    highestScore = moveScore;
                    highestScoreRow = rowIterator; highestScoreCol = colIterator;
                }
            }
        }
    }    
    for(int rowIterator = 1; rowIterator < n - 3; rowIterator ++) {
        for(int colIterator = 2; colIterator < n - 2; colIterator ++) {
            if(checkFullDirectionalLegality(hypotheticalBoard, n, rowIterator, colIterator, turn)){
                int moveScore = evaluateMove(hypotheticalBoard, n, rowIterator, colIterator, turn);
                if(moveScore == highestScore && highestScore > 0) {
                    if(rowIterator == highestScoreRow && colIterator < highestScoreCol) {highestScoreRow = rowIterator; highestScoreCol = colIterator;}
                    else if(rowIterator < highestScoreRow) {highestScoreRow = rowIterator; highestScoreCol = colIterator;}
                }
                else if(moveScore > highestScore) {
                    highestScore = moveScore;
                    highestScoreRow = rowIterator; highestScoreCol = colIterator;
                }
            }
        }
    }
    for(int rowIterator = 0; rowIterator < n; rowIterator += n - 1) {
        for(int colIterator = 0; colIterator < n; colIterator += n - 1) {
            if(checkFullDirectionalLegality(hypotheticalBoard, n, rowIterator, colIterator, turn)){
                int moveScore = evaluateMove(hypotheticalBoard, n, rowIterator, colIterator, turn);
                if(moveScore == highestScore && highestScore > 0) {
                    if(rowIterator == highestScoreRow && colIterator < highestScoreCol) {highestScoreRow = rowIterator; highestScoreCol = colIterator;}
                    else if(rowIterator < highestScoreRow) {highestScoreRow = rowIterator; highestScoreCol = colIterator;}
                }
                else if(moveScore > highestScore) {
                    highestScore = moveScore;
                    highestScoreRow = rowIterator; highestScoreCol = colIterator;
                }
            }
        }
    }

    *row = highestScoreRow; *col = highestScoreCol;
    return 0;
}

//defines logic behind computer's moves
void computerMove(char board[][26], int n, char computerColour, char playerColour) {
    int turn = 0, maxTurns = n * n - 4;
    char currentTurn = 'B', winner = 'U';
    while (turn < maxTurns && (isMoveAvailable(board, n ,'W') || isMoveAvailable(board, n, 'B'))) {
        if (currentTurn == computerColour && isMoveAvailable(board, n, computerColour)) {
            int tempRow, tempCol;
            makeMove(board, n, computerColour, &tempRow, &tempCol);
            printf("Computer places %c at %c%c.\n", computerColour, tempRow + 'a', tempCol + 'a');
            flipTileIfValid(board, n, tempRow, tempCol, computerColour);
            printBoard(board,n);
        }
        else if (currentTurn == computerColour && !isMoveAvailable(board, n, computerColour)) {
            printf("%c player has no valid move.\n", computerColour);
            turn++; 
            if(currentTurn == 'B') currentTurn = 'W';
            else currentTurn = 'B';
        }
        //if it is not the computer's turn, then ensure tiles get flipped based on player's moves
        if(currentTurn != computerColour && isMoveAvailable(board,n,playerColour)) {
            char nextPlayerMove[2];
            printf("Enter move for colour %C (RowCol): ", playerColour);
            scanf("%s", nextPlayerMove);
            char playerNextRow = nextPlayerMove[0] - 'a'; char playerNextCol = nextPlayerMove[1] - 'a';	
            if(checkFullDirectionalLegality(board, n, playerNextRow, playerNextCol, playerColour)) {
                flipTileIfValid(board, n, playerNextRow, playerNextCol, playerColour);
                printBoard(board,n);
            }
            else {
                printf("Invalid move.\n");
                turn = n * n - 4;
                winner = computerColour;
            }
            //currentTurn = computerColour;
        }
        else if (currentTurn != computerColour && !isMoveAvailable(board,n,playerColour)) {
            printf("%c player has no valid move.\n", playerColour);
            turn++; 
            if(currentTurn == 'B') currentTurn = 'W';
            else currentTurn = 'B';
        }

        turn++; 
        if(currentTurn == 'B')
            currentTurn = 'W';
        else
            currentTurn = 'B';
        
    }

    if(winner != 'U')
        printf("%c player wins.\n", computerColour);

    else{
        int BCounter = 0, WCounter = 0;
        for(int rowIterator = 0; rowIterator < n; rowIterator ++) {
            for(int colIterator = 0; colIterator < n; colIterator ++) {
                if(board[rowIterator][colIterator] == 'B') BCounter++;
                if(board[rowIterator][colIterator] == 'W') WCounter++;
            }
        }
        if(BCounter > WCounter) {winner = 'B'; printf("%c player wins.\n", winner);}
        else if(WCounter > BCounter) {winner = 'W'; printf("%c player wins.\n", winner);}
        else {winner = 'D'; printf("Draw!\n");}
    }
}
/*
#ifndef COMPETE_MODE // DO NOT DELETE THIS LINE
int main(void) {
    // Complete your main function here
    //initialize variable and character arrays
    int n;
    char board[26][26], playerColour, computerColour;

    //get initial input on board dimensions
    printf("Enter the board dimension: ");
    scanf("%i", &n);

    //initialize and configure the board
    initializeBoard(board, n);
    printf("Computer plays (B/W) : ");
    scanf(" %c", &computerColour);

    if(computerColour == 'B')
        playerColour = 'W';
    else
        playerColour = 'B';
    printBoard(board, n);
    computerMove(board, n, computerColour, playerColour);
    return 0;
}
#endif // DO NOT DELETE THIS LINE
*/
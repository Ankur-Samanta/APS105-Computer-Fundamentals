#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define BOARDROWS 9
#define BOARDCOLS 11

bool dumpComputer = true; //causes dump of computer board before game if true (fordebugging); change to false for submission

// boards. 0 means empty, non-zero means ship is there, number is size, -tive meanshit on a ship
int playerBoard[BOARDROWS + 1][BOARDCOLS + 1];
int computerBoard[BOARDROWS + 1][BOARDCOLS + 1];
int compShotBoard[BOARDROWS + 1][BOARDCOLS + 1];

int getRand(int lowval,int highval){    
    return (rand() % (highval + 1 - lowval) + lowval);
}

int getShot(bool fromUser, int board[BOARDROWS + 1][BOARDCOLS + 1]){    
    int row,col;    

    while(1){        
        if(fromUser){            
            printf("Give a shot (row, col):");            
            scanf("%d%d",&row,&col);            
            if(col<1 || col > BOARDCOLS || row < 1 || row > BOARDROWS)                
                printf("Invalid input\n");            
            else  //valid input                
                break;        
        }        
        else { //computer generated            
            row=getRand(1,BOARDROWS);            
            col=getRand(1,BOARDCOLS);            
            if(compShotBoard[row][col] == 0) { //make sure haven't shot here before                
                compShotBoard[row][col] = 1; //valid shot                
                break;            
            }        
        }    
    } //will leave this loop with valid input    
    if(board[row][col] != 0){        
        if(board[row][col] > 0)            
            board[row][col]= -1 * board[row][col]; //make sure is -tive        
        return -1 * board[row][col]; //a hit!    
    }    
    return 0; //miss
}
    
bool allShipsNotHit(int board[BOARDROWS + 1][BOARDCOLS + 1]){    
    for(int i = 1;i <= BOARDROWS;i++){        
        for(int j = 1;j <= BOARDCOLS;j++){            
            if(board[i][j] > 0) //ship and not hit                
                return(true);
        }    
    }    
    return (false); //no ships found not all hit
}

bool noneLeft(int valueToFind,int board[BOARDROWS + 1][BOARDCOLS + 1]){    
    for(int i = 1;i <= BOARDROWS;i++){        
        for(int j = 1;j<=BOARDCOLS;j++){            
            if(board[i][j] == valueToFind) //ship and not hit                
                return(false);        
        }    
    }    
    return (true); //no ships found, all hit
}

//Below is Code that I wrote

void populateBoard(bool getUserInput, int board[BOARDROWS + 1][BOARDCOLS + 1]){    
    //******* YOUR CODE GOES HERE TO POPULATE THE BOARDS    
    //**** use subroutines (other functions you generate) to make your code easier to understand and more organized    
    //**** do not (permanently) alter any other code please
    //initialize variables
    int row, col, orientation, shipLength, isSpaceOccupied;
    //set initial shiplength value as 5
    shipLength = 5;
    //Computer input
    if (getUserInput == false) {
		while (shipLength > 0){
            //assign random values
			row = getRand(1, BOARDROWS), col = getRand(1, BOARDCOLS), orientation = getRand(0, 1);
            isSpaceOccupied = 0; //nothing is occupying the space initially
			//horizontal orientation
			if (orientation == 0){
			//check for valid input	
                if (row > 0 && col > 0 && row <= BOARDROWS && col <= BOARDCOLS + 1 - shipLength){
					for (int iterator = col; iterator < col + shipLength; iterator++){
						if (board[row][iterator] != 0){ 
							isSpaceOccupied = 1; //something is occupying the space
							break;
						}
					}
					//if nothing occupying the space already, adjust value with updated shiplength
                    if (isSpaceOccupied == 0){
						for (int iterator = col; iterator < col + shipLength; iterator++){
							board[row][iterator] = shipLength;
						}
						//iterate to check the next shiplength
                        shipLength--;
					}
				}
			}
            //vertical orientation
            else if (orientation == 1){
                //check for valid input
				if (row > 0 && col > 0 && row <= BOARDROWS+ 1 - shipLength && col <= BOARDCOLS){
					//check for conflicts
                    for (int iterator = row; iterator < row + shipLength; iterator++){
						if (board[iterator][col] != 0){
							isSpaceOccupied = 1;
							break;
						}
					}
					if (isSpaceOccupied == 0){
						for (int iterator = row; iterator < row + shipLength; iterator++){
							board[iterator][col] = shipLength;
						}
						shipLength--;
					}
				}
			}
		}
	}
    //user
    else if (getUserInput == true) {
        printf ("Rows are 1 - 9, Columns are 1 - 11\n");
		printf ("Orientation is 0 for across, 1 for down\n");
        //Cycling through ships of length 5 to 1
        shipLength = 5;
        while (shipLength > 0) {
            isSpaceOccupied = 0;
			printf("Give starting row, starting column and orientation (3 inputs) for ship of size=%d:", shipLength);
			scanf ("%d%d%d", &row, &col, &orientation);
            //horizontal orientation
            if (orientation == 0) {
                //validity of input
                if (row > 0 && col > 0 && row <= BOARDROWS && col <= BOARDCOLS + 1 - shipLength) {
                    //check for conflicts
                    for (int iterator = col; iterator < col + shipLength; iterator++) {
                        if (board[row][iterator] != 0) {
                            isSpaceOccupied = 1; //this means there is a conflict
                            break;
                        }
                    }
                    if (isSpaceOccupied == 0) {
                        for (int iterator = col; iterator < col + shipLength; iterator++) {
                            board[row][iterator] = shipLength;
                        }
                        shipLength--;
                    }
                    else{
						printf ("Conflicts with ship already placed\n");
					}
                }
                else{
				    printf ("Invalid Input\n");
			    }
            }
            //vertical orientation
            else if (orientation == 1) {
                //validity of input
                if (row > 0 && col > 0 && row <= BOARDROWS + 1 - shipLength && col <= BOARDCOLS) {
                    //check for conflicts
                    for (int iterator = row; iterator < row + shipLength; iterator++) {
                        if (board[iterator][col] != 0) {
                            isSpaceOccupied = 1;
                            break;
                        }
                    }
                    if (isSpaceOccupied == 0) {
                        for (int iterator = row; iterator < row + shipLength; iterator++) {
                            board[iterator][col] = shipLength;
                        }
                        shipLength--;
                    }
                    else{
						printf ("Conflicts with ship already placed\n");
				    }
                }
                else{
                    printf ("Invalid Input\n");
                }
            }
            else {
			    printf ("Invalid Input\n");
			}
        }
    }
}
    
//Skeleton code resumes below

void showBoard(int board[BOARDROWS + 1][BOARDCOLS + 1]){    
    printf("   Cols\n");    
    printf("    1  2  3  4  5  6  7  8  9 10 11\n");    
    printf("     ________________________________\n");    
    for(int i = 1;i <= BOARDROWS;i++){        
        printf("R%d|",i);        
        for(int j = 1;j <= BOARDCOLS;j++){            
            if(board[i][j]>=0)                
                printf(" ");            
            printf("%d ",board[i][j]);        
        }        
        printf("|\n");    
    }    
    printf("  __________________________________\n");
}

int main(int argc, char **argv){    
    bool playerBoardOK,computerBoardOK;    
    // initialize the seed randomly. 
        srand(time(NULL));     
    //init the boards    
    for(int i = 0;i < BOARDROWS;i++){        
        for(int j = 0;j < BOARDCOLS;j++){            
            playerBoard[i][j] = 0;            
            computerBoard[i][j] = 0;            
            compShotBoard[i][j] = 0;        
        }
    }    
    populateBoard(true,playerBoard);    
    populateBoard(false,computerBoard);    
    printf("Your board is\n");    
    showBoard(playerBoard);    
    if(dumpComputer){        
        printf("\n\nComputer board is\n");        
        showBoard(computerBoard);    
    }    
        
    // play starts here    
    playerBoardOK = true;    
    computerBoardOK = true;    
    while(playerBoardOK && computerBoardOK){        
        int hit=getShot(true,computerBoard); //shot from user        
        if(hit){            
            printf("HIT on size %d\n",hit);            
            if(noneLeft(hit,computerBoard))                
                printf("Sunk computer's %d\n",hit);        
        }        
        else            
            printf("MISS!!\n");        
        hit=getShot(false,playerBoard);        
        if(hit){            
            printf("Computer hits! Size=%d\n", hit);            
            if(noneLeft(hit,playerBoard))                
                printf("Sunk your %d\n",hit);        
        }        
        else            
            printf("Computer miss!\n");        
        playerBoardOK = allShipsNotHit(playerBoard);        
        computerBoardOK = allShipsNotHit(computerBoard);
//    showBoard(playerBoard); //debug
//    showBoard(computerBoard); //debug   
    }   
    if(playerBoardOK)       
        printf("You win!\n");    
    else        
        printf("You lose.\n");    
    showBoard(computerBoard);
            
    return 0;
}
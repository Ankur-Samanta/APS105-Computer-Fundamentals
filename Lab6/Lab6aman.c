#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define BOARDROWS 9
#define BOARDCOLS 11

bool dumpComputer = false; //causes dump of computer board before game if true (for debugging)

// boards. 0 means empty, non-zero means ship is there, number is size, -tive means hit on a ship
int playerBoard[BOARDROWS+1][BOARDCOLS+1];
int computerBoard[BOARDROWS+1][BOARDCOLS+1];
int compShotBoard[BOARDROWS+1][BOARDCOLS+1];

int getRand(int lowval,int highval){
    return (rand()%(highval+1-lowval) + lowval);
}




int getShot(bool fromUser, int board[BOARDROWS+1][BOARDCOLS+1]){
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
            if(compShotBoard[row][col]==0) { //make sure haven't shot here before
                compShotBoard[row][col]=1; //valid shot
                break;
            }
        }
    } //will leave this loop with valid input
    if(board[row][col] != 0){
        if(board[row][col]>0)
            board[row][col]= -1*board[row][col]; //make sure is -tive
        return -1*board[row][col]; //a hit!
    }
    return 0; //miss
}
            

bool allShipsNotHit(int board[BOARDROWS+1][BOARDCOLS+1]){
    for(int i=1;i<=BOARDROWS;i++){
        for(int j=1;j<=BOARDCOLS;j++){
            if(board[i][j]>0) //ship and not hit
                return(true);
        }
    }
    return (false); //no ships found not all hit
}

bool noneLeft(int valueToFind,int board[BOARDROWS+1][BOARDCOLS+1]){
    for(int i=1;i<=BOARDROWS;i++){
        for(int j=1;j<=BOARDCOLS;j++){
            if(board[i][j]==valueToFind) //ship and not hit
                return(false);
        }
    }
    return (true); //no ships found, all hit
}

//function for populating board
void populateBoard (bool getUserInput, int board[BOARDROWS + 1][BOARDCOLS + 1]){
	//start by defining variables  for orientation (horiVerti), row(i) and column(j)
    int horiVerti, i, j, k = 5, a, check;
	//Player Board
    if (getUserInput == true){
		printf ("Rows are 1 - 9, Columns are 1 - 11\n");
		printf ("Orientation is 0 for across, 1 for down\n");
		while (k > 0){
			check = 1;
			printf("Give starting row, starting column and orientation (3 inputs) for ship of size=%d:",k);
			scanf ("%d%d%d", &i, &j, &horiVerti);
			//case for downwards orientation
            if (horiVerti == 1){
				//check for valid input
                if (i > 0 && j > 0 && i <= BOARDROWS+ 1 -k && j <= BOARDCOLS){
					//check for conflicts
                    for (a = i; a < i + k; a++){
						if (board[a][j] != 0){
							check = 0;
							break;
						}
					}
					if (check == 1){
						for (a = i; a < i + k; a++){
							board[a][j] = k;
						}
						k--;
					}
					else{
						printf ("Conflicts with ship already placed\n");
					}
				}
				else{
					printf ("Invalid Input\n");
				}
			}
            //case for horizontal orientation
			else if (horiVerti == 0){
				//check for valid input
                if (i > 0 && j > 0 && i <= BOARDROWS && j <= BOARDCOLS+1-k){
					//check for conflicts
                    for (a = j; a < j + k; a++){
						if (board[i][a] != 0){
							check = 0;
							break;
						}
					}
					if (check == 1){
						for (a = j; a < j + k; a++){
							board[i][a] = k;
						}
						k--;
					}
					else{
						printf ("Conflicts with ship already placed");
					}
				}
				else{
					printf ("Invalid Input\n");
				}
			}
			else{
				printf ("Invalid Input\n");
			}
		}
	}
    //Computer Board
	else{
		while (k > 0){
			i = getRand(1, BOARDROWS);
			j = getRand(1, BOARDCOLS);
			horiVerti = getRand(0, 1);
            check = 1;
			if (horiVerti == 1){
            //check for valid input
				if (i > 0 && j > 0 && i <= BOARDROWS+ 1 -k && j <= BOARDCOLS){
					//check for conflicts
                    for (a = i; a < i + k; a++){
						if (board[a][j] != 0){
							check = 0;
							break;
						}
					}
					if (check == 1){
						for (a = i; a < i + k; a++){
							board[a][j] = k;
						}
						k--;
					}
				}
			}
			else if (horiVerti == 0){
			//check for valid input	
                if (i > 0 && j > 0 && i <= BOARDROWS && j <= BOARDCOLS+1-k){
					for (a = j; a < j + k; a++){
						if (board[i][a] != 0){
							check = 0;
							break;
						}
					}
					if (check == 1){
						for (a = j; a < j + k; a++){
							board[i][a] = k;
						}
						k--;
					}
				}
			}
		}
	}
}

void showBoard(int board[BOARDROWS+1][BOARDCOLS+1]){
    printf("   Cols\n");
    printf("    1  2  3  4  5  6  7  8  9 10 11\n");
    printf("     ________________________________\n");
    for(int i=1;i<=BOARDROWS;i++){
        printf("R%d|",i);
        for(int j=1;j<=BOARDCOLS;j++){
            if(board[i][j]>=0)
                printf(" ");
            printf("%d ",board[i][j]);
        }
        printf("|\n");
    }
    printf("  __________________________________\n");
}

int main(int argc, char **argv)
{
    bool playerBoardOK,computerBoardOK;
    
    // initialize the seed randomly. 

     	srand(time(NULL)); 

    //init the boards
    for(int i=0;i<BOARDROWS;i++){
        for(int j=0;j<BOARDCOLS;j++){
            playerBoard[i][j]=0;
            computerBoard[i][j]=0;
            compShotBoard[i][j]=0;
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
    playerBoardOK=true;
    computerBoardOK=true;
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
            if(noneLeft(hit,computerBoard))
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
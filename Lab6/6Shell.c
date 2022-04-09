#include <stdio.h>
#include <math.h>

bool clash(int board[BOARDROWS + 1][BOARDCOLS + 1], int row, int col, int orientation, int length) {
    for(int i = 0; i < length; i++) {
        if(orientation == 1) {
            if(board[row + i][col] != 0) {
                return false;
            }
        }
        else {
            if(board[row][col + i] != 0) {
                return false;
            }
        }
    }
    return true;
}

void populateBoard(bool getUserInput, int board[BOARDROWS+1][BOARDCOLS+1]) {
    int row, col, orientation;

    if(getUserInput) {
        printf("Rows are 1 - 9, Columns are 1 - 11\n");
        printf("Orientation is 0 for across, 1 for down\n");
    
        for(int length = 5; length > 0; length--) {
            if(getUserInput){
                printf("Give starting row, starting column and orientation (3 inputs) for ship of size=%d:", length);
                scanf("%i %i %i", &row, &col, &orientation);
            }
            else {
                row = rand() % 9 + 1;
                col = rand() % 11 + 1;
                orientation = rand() % 2;
            }
            if(row < 1 || row > BOARDROWS || col < 1 || col > BOARDCOLS || orientation < 0 || orientation < 1 || (orientation == 0 && length + col > BOARDCOLS) || (orientation == 1 && row + length > BOARDROWS)) {
                if(getUserInput) {
                    printf("Invalid Input\n");
                    length++;
                }
            }
            else {
                if(clash(board, row, col, orientation, length)) {
                populate(board, row, col, orientation, length);
                }
                else {
                if(getUserInput) {
                    printf("Conflicts with ship already placed\n");
                    length++;
                }
            }
        }
    }
    return;
}
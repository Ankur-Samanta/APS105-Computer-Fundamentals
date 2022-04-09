#include <stdio.h>

void printNChar(int numC, char c) { //given
    for (int i = 1; i <= numC; i++)
    printf("%c", c);
}

int main () {
    int num; char display = '@'; //initialize input variable and character that will be displayed
    printf("Enter an integer value (num): ");
    scanf("%d", &num);
    printNChar(num, display); //prints the first row
    printf("\n");
    for (int row = 0; row < num - 2; row++) { //goes through row 2 through row num - 1; so, num - 2 rows are iterated through
        printNChar(1, display); //this prints just one @ at the leftmost margin of the array created for each row
        for (int col = 0; col < num - 2; col++) {  //goes through col 2 through col num - 1; so, num - 2 cols are iterated through
            if (row == col) printNChar(1, display); //this is the condition for the diagonal, and if met, print a single @
            else printf(" "); //' ' if it is not on the diagonal
        }
        printNChar(1, display); //prints just one @ at the rightmost margin of the array created for each row
        printf("\n");
    }
    printNChar(num, display); //prints the nth (last) row
    return 0;
}
//Name: Ankur Samanta
//ID: 1006917632
//Class: APS105
//Assignment: Lab 4 Part 2
//Objective: Form triangles of asterisks depending on how many rows the traingle is supposed to have

//load libraries
#include <stdio.h>
#include <math.h>

int main (void) {
    //initialize variable names
    int totalRows, row, spaces, middleSpaces, asterisk;
    //user input to determine the total number of rows in the triangle
    printf("Enter the number of rows in the triangle: ");
    scanf("%d", &totalRows);
    //for(initialvalue; condition; increment) {statement();}
    for(row = 1; row <= totalRows - 1; row +=1) {
        //the below loops will run for each of the individual rows; once the loops have run their course, the row number will incrementally increase by 1
        //then, the below processes will repeat for the new row number, and this will continue until we have reached the row prior to the total number of rows there should be
        //we first print the spaces that should occur to the left of the first asterisk in each row
        //the spaces in this part of each row will equal the difference between the total number of rows and the number of the row we are on
        for(spaces = 1; spaces <= totalRows - row; spaces += 1) {
            printf(" ");
        }
        //then, we will print the first asterisk
        printf("*");
        //now, we have to determine how many spaces occur between the first and last asterisk in each row (excluding the final row)
        //this is done by subtracting 3 from double the row number, and spaces will be incrementally added until we reach that number
        for(middleSpaces = 1; middleSpaces <= 2 * row - 3; middleSpaces +=1) {
            printf(" ");
        }
        //then, for every row that is not the first row or the last row, we will add the last asterisk of the row after the spaces
        if (row > 1) {
            printf("*");
        }
        //now that everything that needs to be printed for this row has been printed, we move onto the next line, the row number is increased by 1, and the loop starts again
        printf("\n");
    }
    //this addresses the last row of the asterisk triangle
    //the total number of asterisks in this row will simply be 1 less than twice the number of rows in the triangle
    for(asterisk = 1;asterisk <= 2 * row - 1; asterisk += 1) {
        printf("*");
    }
    //complete program
    return 0;
}
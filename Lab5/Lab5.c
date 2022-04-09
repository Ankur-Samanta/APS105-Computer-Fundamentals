//Name: Ankur Samanta
//ID: 1006917632
//Class: APS105
//Assignment: Lab 5
//Objective: Print Pascal's Triangle

//import libraries
#include <stdio.h>

//function declaration (defined after main body of function)
int factorial(int n);
int choose(int n, int r);
void triangle(int rows);
int digits(int c);
void spaces(int d);

//main body of program which collects user input on the total number of rows and prints out Pascal's triangle using the functions defined below the main body
int main () {
    int rows;
    printf("Enter the number of rows: ");
    scanf("%d", &rows);
    while (rows >= 0) {
        triangle(rows);
        printf("Enter the number of rows: ");
        scanf("%d", &rows);
    }
    return 0;
}

//definition of function that calculates the factorial value of n using recursion
int factorial(int n) {
    int result;
    if (n >= 1) {
        return n * factorial(n - 1);
    }
    else {
        return 1;
    }
}

//definition of function that calculates the combinatorics value of n choose r
int choose(int n, int r) {
    int result = factorial(n) / (factorial(r) * factorial(n - r));
    return result;
}

//definition of function that recursively calculates the number of digits in an integer c
int digits(int c) {
    if (c < 10) {
        return 1;
    }
    return 1 + digits(c / 10);
}

//definition of function that iteratively determines how many spaces to print based on the number of digits d in an integer c
void spaces(int d) {
    //e is the index of the digit we are adding the space for
    int e;
    for (e = 1; e <= 6 - d; e += 1) {
        printf(" ");
    }
}

void triangle(int rows) {
    //space represents the number of spaces that occur before the first value is printed in each row
    //a represents the number of the row the program is on, with the index starting from 0
    //b represents the number of the value the program is on in the given row, with index starting from 0
    int space, a, b;
    //loop below runs for each of the rows
    for (a = 0; a <= rows - 1; a += 1) {
        //prints the appropriate number of spaces that should occur before the first value is printed in the row
        //for (space = 1; space <= rows - (a+1); space += 1) {
        for (space = 1; space <= 3 * (rows - (a + 1)); space += 1) {
            printf(" ");
        }
        //prints the combinatorics value and a space for each index in the row, total number of values in the row is the same as the row number
        for (b = 0; b <= a; b += 1) {
            printf("%d", choose(a, b));
            spaces(digits(choose(a, b)));
        }
        printf("\n");
    }
}
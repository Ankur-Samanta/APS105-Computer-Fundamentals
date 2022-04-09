//Name: Ankur Samanta
//ID: 1006917632
//Class: APS105
//Assignment: Lab 4 Part 1
//Objective: Break down a given monetary amount into coins

//load libraries
#include <stdio.h>
#include <math.h>

int main (void) {
    //initialize variables
    int amount, quarters, dimes, nickels, cents;
    //user input to determine the total number of cents
    printf("Please give an amount in cents less than 100: ");
    scanf("%d", &amount);
    //as long as the amount entered is valid (greater than equal to 1, and less than equal to 99), the following code is run
    while (amount >= 1 && amount <= 99) {
        //the below logic block will be used to determine the tense of the monetary unit when printed.
        //it will be repeated at every iteration of the code as we go through each of the monetary units
        if (amount > 1) {
            printf("%d cents: ", amount);
        }
        else if (amount == 1) {
            printf("%d cent: ", amount);
        }
        //quarters can be used only if the amount is greater than 25
        //note that the below loop for quarters will be repeated afterwards for each of the successively smaller monetary units
        if (amount >= 25) {
            //find number of quarters needed by using floor(highest integer value lower than input, in this case the amount divided by the value of the monetary unit)
            quarters = floor(amount / 25);
            //find the new amount of money unaccounted for by subtracting the value of the unit * number of that unit from the amount
            amount -= 25 * quarters;
            //similar logic block to one used from line 19 to 24 to determine tense of the monetary unit
            //print values to breakdown statement accordingly
            if (quarters > 1) {
                printf("%d quarters", quarters);
            }
            else {
                printf("%d quarter", quarters);
            }
            //print "," or "." depending on whether all the amount has been accounted for already or not
            if (amount == 0) {
                printf(".");
            }
            else {
                printf(", ");
            }
        }
        //the above loop runs the same for each of the other monetary units, with the appropriate variables and values being subbed in for each
        if (amount >= 10) {
            dimes = floor(amount / 10);
            amount -= 10 * dimes;
            if (dimes > 1) {
                printf("%d dimes", dimes);
            }
            else {
                printf("%d dime", dimes);
            }
            if (amount == 0) {
                printf(".");
            }
            else {
                printf(", ");
            }
        }

        if (amount >= 5) {
            nickels = floor(amount / 5);
            amount -= 5 * nickels;
            if (nickels > 1) {
                printf("%d nickels", nickels);
            }
            else {
                printf("%d nickel", nickels);
            }
            if (amount == 0) {
                printf(".");
            }
            else {
                printf(", ");
            }
        }
            
        if (amount >= 1) {
            cents = floor(amount / 1);
            amount -= 1 * cents;
            if (cents > 1) {
                printf("%d cents", cents);
            }
            else {
                printf("%d cent", cents);
            }
            if (amount == 0) {
                printf(".");
            }
            else {
                printf(", ");
            }
        }
        //ask for user input again
        printf("\nPlease give an amount in cents less than 100: ");
        scanf("%d", &amount);
    }
    //print Goodbye and then proceed to terminate the program
    printf("Goodbye");
    //program terminated when either all of the original amount has been accounted for and the breakdown has been printed, or the amount given is invalid
    return 0;
}
//Name: Ankur Samanta
//ID: 1006917632
//Class: APS105
//Assignment: Lab 2 Part 2
//Objective: Round the given price of groceries to the nearest nickel

#include <stdio.h>
#include <math.h>

int main (void)
{
    //define input and output variables
    double price, roundedPrice;

    //print input statements, recieve user input for variables, and assign values to corresponding variables
    printf("Enter the price as a float with two decimals: ");
    scanf("%lf", &price);

    //compute the rounded price (rounded to the nearest nickel)
    //since a nickel value is $0.05, in order to use integer rounding, multiply the price by 100
    //now, divide that by 5 to get the exact value of how many nickels there are in the total price
    //then, use the round function to find the nearest integer value of nickels that are in the total price
    //multiply that integer value by 5 and and then divide by 100 to get the new rounded price in dollars
    roundedPrice = ((round((price * 100) / 5) * 5) / 100);

    //print rounded value of original price
    printf("The total charge is: %.2lf\n", roundedPrice);

    //end program
    return 0;
}
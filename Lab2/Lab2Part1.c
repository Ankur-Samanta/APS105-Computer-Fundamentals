//Name: Ankur Samanta
//ID: 1006917632
//Class: APS105
//Assignment: Lab 2 Part 1
//Objective: Calculate the total amount you would pay for groceries at a store with a promotion that offers $0.10 back for every $3 spent

#include <stdio.h>
#include <math.h>

int main (void)
{
    //define the input, intermediary, and output variables, as well as constant value given for rate of savings per $3 spent
    double pricePerPound, totalWeight;
    double originalTotalPrice; 
    double totalCharge, savings;
    double rateOfSavings = 0.10;

    //print input statements, recieve user input for variables, and assign values to corresponding variables
    printf("Enter the price per pound: ");
    scanf("%lf", &pricePerPound);
    printf("Enter the total weight: ");
    scanf("%lf", &totalWeight);

    //define output variables as computations of input variables
    originalTotalPrice = pricePerPound * totalWeight; //find the original total price before any modification or discount
    savings = rateOfSavings * floor((originalTotalPrice / 3)); 
    //find the total resulting charge by subtracting the savings from the original total price
    totalCharge = originalTotalPrice - savings;

    //print the output variables
    printf("The total charge is: %.2lf\n", totalCharge);
    printf("You saved: %.2lf\n", savings);

    //end program
    return 0;
}
//Name: Ankur Samanta
//ID: 1006917632
//Class: APS105
//Assignment: Lab 1
//Objective: Take in 3 double numnbers, then compute and output half their sum, twice their product, and their average

#include <stdio.h>

int main (void)
{
    //define input and output variables
    double inputNumber1, inputNumber2, inputNumber3;
    double halfTheSum, twiceTheProduct, average;

    //print input statements, recieve user input for variables, and assign values to corresponding variables
    printf("Enter First Number: ");
    scanf("%lf", &inputNumber1);
    printf("Enter Second Number: ");
    scanf("%lf", &inputNumber2);
    printf("Enter Third Number: ");
    scanf("%lf", &inputNumber3);

    //define output variables as computations of input variables
    halfTheSum = (inputNumber1 + inputNumber2 + inputNumber3) / 2;
    twiceTheProduct = (inputNumber1 * inputNumber2 * inputNumber3) * 2;
    average = (inputNumber1 + inputNumber2 + inputNumber3) / 3;

    //print output statements with computed output variable values
    printf("Half the Sum: %.2lf\n", halfTheSum);
    printf("Twice the Product: %.2lf\n", twiceTheProduct);
    printf("Average: %.2lf\n", average);

    //end program
    return 0;
}
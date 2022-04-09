//Name: Ankur Samanta
//ID: 1006917632
//Class: APS105
//Assignment: Lab 2 Part 3
//Objective: Calculate the future value of investment assuming compound interest, given the principal, interest rate, number of times the interest is compounded, and the time period of investment

#include <stdio.h>
#include <math.h>

int main (void)
{
    //define input and output variables
    //P: initial deposite amount, or principal
    //r: interest rate
    //n: number of times the interest is compounded during the time period
    //t: period of time the money is invested (in years)
    //A: future value of the investment
    double P, r, n, t;
    double A;

    //print input statements, recieve user input for variables, and assign values to corresponding variables
    printf("The amount deposited P: ");
    scanf("%lf", &P);
    printf("The interest rate r: ");
    scanf("%lf", &r);
    printf("The number of times the interest is compounded n: ");
    scanf("%lf", &n);
    printf("The period of time t the money is invested (in years): ");
    scanf("%lf", &t);

    //computation of future value of investment using compound interest formula
    //A = P*(1+r/n)^(nt)
    A = P * pow((1 + r / n), (n * t));

    //print calculated future value of investment
    printf("The future value of the investment A: %.2lf\n", A);

    //end program
    return 0;
}
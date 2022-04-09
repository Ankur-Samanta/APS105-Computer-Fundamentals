#include <stdio.h>

int main() {
    int integerInput, newDigit, targetDigit, largestDigit = 0; //initialize variables
    printf("Enter an integer: "); scanf("%d", &integerInput); //user input
    newDigit = abs(integerInput); //we only need to look at the input integer's absolute value for this
    while (newDigit != 0) { //as long as the newdigit is not equal to 0,
        targetDigit = newDigit % 10; 
        // this provides us with an integer value that gets rid of the decimals generated as we iterate through the loop and divide by 10 each time (see line 14)
        if (targetDigit > largestDigit && (targetDigit == 4 || targetDigit == 8)) { //only the digits 4 and 8 satisfy the divisibility condition
            largestDigit = targetDigit; 
            /*as long as the digit we are evaluating rn is larger than the current largest digit found, and it is equal to 4 or 8,
            then that new value becomes the new largestdigit*/
        }
        newDigit = newDigit / 10;
        /*we want to truncate any decimals of the value assigned to it, each time we loop through this, we divide the
        number by 10 which gets rid of the digit that we already looked over. Like this, we iterate over all the digits in the number*/
    }
    if (largestDigit == 0) printf("No match found!");
    else {
        printf("\"");
        if (largestDigit == 4) printf("FOUR is the largest digit!\"");
        else if (largestDigit == 8) printf("EIGHT is the largest digit!\"");
    }
    return 0;
}
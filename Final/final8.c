#include <stdio.h>
#include <stdbool.h>

// please use this prototype without any changes or alterations
bool canMakeSum(int inputArray[], int arraysize, int targetSum) { //returns true if there are elements in the array that sum to targetSum
  


}



/*** here is some code you can use to test yours. 
/*** BE SURE TO TAKE IT OUT BEFORE YOUR FINAL SUBMIT!!!!!
int main(int argc, char **argv)
{
    int myArray[25];
    int testvals[20];
    int arraySize,testValueSize;
  
    //get size of array of values that are summed
    arraySize=250;
    while(arraySize<0 || arraySize >25){
        printf("Give size of array of values that are summed (up to 25)");
        scanf("%d",&arraySize);
    }
    // get array of values to use
    for(int i=0;i<arraySize;i++){
        printf("Give a value for the array whose values are summed:");
        scanf("%d",&myArray[i]);
    }
    //get number of values to try
    testValueSize=250;
    while(testValueSize<0 || testValueSize >20){
        printf("Give number of test values you want to try (up to 20)");
        scanf("%d",&testValueSize);
    }
    //get an array of target values to try
     for(int i=0;i<testValueSize;i++){
        printf("Give a value for the array to test against:");
        scanf("%d",&testvals[i]);
    }
   
    for(int i=0;i<testValueSize;i++){
        if(canMakeSum(myArray,arraySize,testvals[i])) 
            printf("%d is possible\n",testvals[i]);
        else
            printf("%d is NOT possible\n",testvals[i]);
    } 
	return 0;
}
**/
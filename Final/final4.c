#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *acronymMaker(char *inString) {
    char *acronym, newAcronym[150]; //create an array that will house the characters of the acronym
    char initialString[150]; //array containing characters of initial string
    strcpy(initialString, inString); //strcpy copies the string pointed by source to the destination
    int count; //counter variable
    char *ch = strtok(initialString, " ");//breaks initialString into tokens, or smaller strings; " " is delim, and returns a pointer to the first token
    while (ch != NULL) { //as long as there are tokens left to retrieve at the memory address returned by strtok
        //below if statement allows us to check for whether there are any tokens equal to the words we are supposed to ignore
        if (!(strncmp(ch,"the", 3)) == 0 && !(strncmp(ch, "of", 2)) == 0 && !(strncmp(ch,"an", 2)) == 0 && !(strncmp(ch, "and", 3)) == 0 && !(strncmp(ch, "a", 1)) == 0 && !(strncmp( ch, "to", 2)) == 0){
            newAcronym[count] = ch[0]; 
            /*if a token exists that when compared to the strings we want to weed out is equivalent (found using strcmp), 
            we do not want to carry over the token to the newAcronym array.
            So, we set the count value to 0 (essentially ignoring that token)
            Then, up the count and continue, checking each of the tokens each time for any 
            instance where there aren't 0 matches with the aforementioned terms*/
            count++; 
        }
        ch = strtok(NULL, " "); // (reading the next word)
    }
    acronym = (char*)malloc(sizeof(char)*(count+1)); //allows us to dynamically allocate the final acronym array based on the count after looping through all the tokens
    acronym = newAcronym;
    acronym[count+1] = '\0'; //indicate termination of character string for the acronym
    return acronym; //return the acronym
}
#include <stdio.h>
#include <stdint.h>

void removeDup(char * list, int stringLength){
    for(int iterator1 = 0; iterator1 < stringLength; iterator1++){ //go through all array elements
        for(int iterator2 = iterator1 + 1; list[iterator2] != '\0'; iterator2++){ //start from the next element, and iterate as long as its not the last term
            if(list[iterator2] == list[iterator1]){ // if 2 adjacent elements are equal
                for(int iterator3 = iterator2; list[iterator3] != '\0'; iterator3++){ //find next to next element
                    list[iterator3] = list[iterator3 + 1]; //shift everything back 1
                }
            }
        }
    }
}

void removeSpaces(char *list){
    int i = 0, j = 0; //initialize iterators
    while(list[i]){ //while a term exists in the list at that spot
        if(list[i] != ' ') //it that is not a space
        list[j++] = list[i]; //j is counter for list without spaces, and i is counter for list with spaces
        //so, if there is no space, both i and j jump, but if there is a space, then j shouldn't jump but i does
        //if there is a space, then i increases, but if there isn't, then both increase. j is always <= i, and it will copy in the values of i; j is changing the previous elements, and the head, elements that i are touching, are not impacted before j gets there
        i++;
    }
    list[j] = '\0'; //finishing the string
}

void bubbleSortChar(char list[]) {
    int length = strlen(list);
    char temp;

    for(int iterator1 = 1; iterator1 < length; iterator1++){ //go through all array elements
        //last iterator1 elements are already in place
        for(int iterator2 = 0; iterator2 < length - iterator1; iterator2++){ //traverse array from 0 to length - iterator1
            if((int)list[iterator2] >= (int) list[iterator2 + 1]){ //if the element found is greater than the next element
                //swap
                temp = list[iterator2];
                list[iterator2] = list[iterator2 + 1];
                list[iterator2 + 1] = temp;
            }
        }
    }
removeSpaces(list);
removeDup(list, length);
}
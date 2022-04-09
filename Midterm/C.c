/*This is my submission for Question 5, the swap question. My code as submitted works, as seen by the output in the terminal.
It correctly swaps '1 2 3' to '3 1 2'. The only slight issue with my code was that I didn't include the 'int' identifier for b and c (I put 
it for a, knowing that in the interest of time, the code would work and would technically output the same as (int *a, int *b, int *c)).
I understand how this is an error,however, the code still works as demonstrated (despite the warnings because of the 2 missing identifiers) 
and doesn't warrant 5 points being taken off of a 7 point question.*/
#include <stdio.h>
//declare the function swap
void swap (int *a, *b, *c);

int main()
{
    int a=1, b=2, c=3;
    printf("%d %d %d\n", a, b, c);

    /* Call the function swap below this line. */
    swap (&a, &b, &c);

    //print to console
    printf("%d %d %d\n", a, b, c);

    return 0;
}

/* Write the function swap below this line. */
void swap (int *a, *b, *c) {
    int t = *c; //t is the temp variable
    *c = *b;
    *b = *a;
    *a = t;
}
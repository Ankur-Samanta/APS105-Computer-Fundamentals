//Name: Ankur Samanta
/*This is the corrected version of my submission to examify. It has very minor edits that make the code work, that I was not able 
to update on the examify server on time since I ran out of time; however, I do believe that the 3 minor edits needed to fix the 
code was not 8 points worth of errors.*/
#include <stdio.h>

int main(void) {
	int row, col, num;

	printf("Enter the number of rows in the triangle: ");
	scanf("%d", &num);

	while(num >= 0) {
		for (row = 1; row <= num; row++) {
			for (col = 1; col < 2 * num; col++) {
				if (row - col == 0) {
					printf("*");
				}
				else if(row == 1) {
					printf("*");
				}
				else if(col + row == 2 * num) {
					printf("*");
				}
				else {
                    if (row != num) {
                        printf(" ");
                    }
					else if(col != 2 * num - 1) {
						printf(" ");
					}
				}
			}
            printf("\n");
        }
	printf("Enter the number of rows in the triangle: ");
    scanf("%d", &num);
	}
	printf("Goodbye\n\n");
	return 0;
}
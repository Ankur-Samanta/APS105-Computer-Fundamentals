//Name: Ankur Samanta
//This is my actual submission to examify for question 9

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
                    //missing if statement here accounting for condition where row is not equal to col (in which case, print a space)
					else if(col! = 2 * num - 1) { //mistype, should be 'col !=', not 'col! ='
						printf(" ");
					}
				}
				//below print statement in wrong position, should be outside of this loop, after end bracket at line 32
				printf("\n");
			}
			//below print and scan pair in wrong position, should be outside of this loop, after end bracket at line 36
			printf("Enter the number of rows in the triangle: ");
			scanf("%d", &num);
		}
	}
	printf("Goodbye\n\n");
	return 0;
}
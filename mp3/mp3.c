/*
 * This program prints a specific row of Pascal's Triangle.  The row that is 
 * printed is specified by the user.  This is done using a for loop and the
 * binomial coefficient formula to calculate the coefficients of the specified 
 * row.  The coefficients are then printed to the screen
 */
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int row;

	printf("Enter a row index: ");
	scanf("%d",&row);

	// Write your code here
	// Declare Variable to hold coefficient, initialize to 1
	unsigned long coeff = 1;

	// Each row starts with 1, so print 1 at start of each row
	printf("1 ");
	
	// Loop through each k
	for(int k=1; k<=row; k++)
	{	
		// Calculate the coefficient for each value of k
		coeff = (coeff * (row + 1 - k))/k;
		// Print the current coefficient
		printf("%lu ", coeff);
	}
	// Go to next line
	printf("\n");

  return 0;
}

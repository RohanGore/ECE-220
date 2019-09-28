/* Code to simulate rolling three six-sided dice (D6)
 * User first types in seed value
 * Use seed value as argument to srand()
 * Call roll_three to generate three integers, 1-6
 * Print result "%d %d %d "
 * If triple, print "Triple!\n"
 * If it is not a triple but it is a dobule, print "Double!\n"
 * Otherwise print "\n"
 */
#include <stdlib.h>
#include <stdio.h>
#include "dice.h"

int main()
{
	int seed;
	// Prompt User for seed input
	printf("Enter seed: ");
	// Read user input
	scanf("%d", &seed);
	
	// Declaration of variables to hold random numbers
	int one, two, three;

	// Set seed using srand()
	srand(seed);
	// Call roll_three functin passing variables by reference
	roll_three(&one, &two, &three);

	// Print random numbers	
	printf("%d %d %d ", one, two, three);
	// Check if number is a triple
	if(one == two && two == three)	
		printf("Triple!\n");
	// Check if number is a double
	else if(one == two && two != three)
		printf("Double!\n");
	else if(one == three && two != three)
		printf("Double!\n");
	else if(two == three && two != one)
		printf("Double!\n");
	else
		printf("\n");


	return 0;
}


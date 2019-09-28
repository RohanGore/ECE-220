#include <stdio.h>
#include <math.h>

#define M_PI 3.14159265358979323846

/*
 * main
 *  DESCRIPTION: compute a set of points of a function and print the results
 *  INPUTS: console (int, float float) -- equation related constants
 *  OUTPUTS: console (x, f(x)) -- sequence of values to be printed
 *  RETURN VALUE: 0
 *  SIDE EFFECTS: none
 */
int main()
{
	// Declare variables
	int n;
	float x, omega1, omega2, result;


	// Prompt user for input
	printf("Enter the values of n, omega1, and omega2 in that order\n");

	// Get user input
	scanf("%d %f %f", &n, &omega1, &omega2);

	// Compute function output
	/* for i from 0 to n-1
     	 * compute and print xi and f(xi)
     	 * use sin() function from math.h
     	 */
	for(int i = 0; i < n; i++)
	{
		x = (i * M_PI)/n;
		result = sin(omega1 * x) + (0.5) * sin(omega2 * x);
		printf("(%f, %f)\n", x, result);
	}




    return 0;
}


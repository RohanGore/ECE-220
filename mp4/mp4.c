/*
 * This program prints all the semiprime numbers in a given range.  A semiprime number is 
 * a number that is the product of two prime numbers.  This is done by implementing a function
 * to determine whether or not a number is prime and implementing a function to print all the 
 * semiprime numbers between two user entered numbers
 */
#include <stdlib.h>
#include <stdio.h>


int is_prime(int number);
int print_semiprimes(int a, int b);


int main(){   
	int a, b;
	printf("Input two numbers: ");
	scanf("%d %d", &a, &b);
	if( a <= 0 || b <= 0 ){
		printf("Inputs should be positive integers\n");
		return 1;
	}

	if( a > b ){
		printf("The first number should be smaller than or equal to the second number\n");
		return 1;
	}

	// TODO: call the print_semiprimes function to print semiprimes in [a,b] (including a and b)
	print_semiprimes(a, b);
	printf("\n");
}	


/*
 * TODO: implement this function to check the number is prime or not.
 * Input    : a number
 * Return   : 0 if the number is not prime, else 1
 */
int is_prime(int number)
{
	// Return 1 if n is a prime, and 0 if it is not
	int result = 1;
	// If the number is 1, return 0 (not prime)
	if(number == 1)
		return 0;
	// Loop through every number from 2 to n-1
	for(int i = 2; i < number; i++)
	{
		// Check if the number is divisible by i
		if(number % i == 0)
		{	
			// If the number is divisible by i, it is not prime
			result = 0;
			// Since the number is not prime, break out of the loop
			break;
		}
	}	
	// Return the result
	return result;
}


/*
 * TODO: implement this function to print all semiprimes in [a,b] (including a, b).
 * Input   : a, b (a should be smaller than or equal to b)
 * Return  : 0 if there is no semiprime in [a,b], else 1
 */
int print_semiprimes(int a, int b)
{
	// Declare variable to return if there are any semiprimes or not between a and b
	int existSemiprime = 0;
	// Loop from a to b
	for(int i = a; i <= b; i++)
	{
		// Loop from 2 to i
		for(int j = 2; j <= i; j++)
		{
			// Check if i is divisible by j and if j is prime
			if(i % j == 0 && is_prime(j) == 1)
			{
				// Check if i/j is prime
				if(is_prime(i / j) == 1)
				{
					// If i is semiprime, print it
					printf("%d ", i);
					// Change return variable to 1
					existSemiprime = 1;
					// Break out of nested for loop to avoid any semiprimes from being printed multiple times
					break;
				}
					
			}
		}
	}
	// Return existSemiprime
	return existSemiprime;
}




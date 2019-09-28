#include <stdio.h>
#include "prime.h"

int main(){
	// Write the code to take a number n from user and print all the prime numbers between 1 and n
	// Declare variables	
	int n, prime;
	// Prompt user for input
	printf("Enter the value of n: ");
	// Get input from user
	scanf("%d", &n);
	printf("Printing primes less than or equal to %d:\n", n);
	// Loop through each number from 1 to n
	for(int i = 1; i <= n; i++)
	{
		// Call function
		prime = is_prime(i);
		// Check if the current number is prime
		if(prime == 1)	
			printf("%d ", i);
	}
	printf("\n");

  return 0;
}


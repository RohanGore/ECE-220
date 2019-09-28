#include "prime.h"

int is_prime(int n){
	// Return 1 if n is a prime, and 0 if it is not
	int result = 1;
	// If the number is 1, return 0 (not prime)
	if(n == 1)
		return 0;
	// Loop through every number from 2 to n-1
	for(int i = 2; i < n; i++)
	{
		// Check if the number is divisible by i
		if(n % i == 0)
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


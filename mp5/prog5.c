/*			
 *
 * prog5.c - source file adapted from UIUC ECE198KL Spring 2013 Program 4
 *           student code -- GOLD VERSION by Steven S. Lumetta
 */


/*
 * The functions that you must write are defined in the header file.
 * Blank function prototypes with explanatory headers are provided
 * in this file to help you get started.
 */

/*
 * INTRO PARAGRAPH
 * -----------------------------------------------------------------------------------------------------
 * This program uses logic to implement a code-breaking game.  The user must first enter a 
 * seed.  This seed value initializes a pseudo-random number generator.  The random number generator
 * creates a solution code sequence of four numbers, each ranging from 1 to 8 chosen at random.
 * The player has 12 chances to guess the solution code.  After each guess the number of perfect matches 
 * misplaced matches are both outputted to the screen
 */

#include <stdio.h>
#include <stdlib.h>

#include "prog5.h"


/*
 * You will need to keep track of the solution code using file scope
 * variables as well as the guess number.
 */

static int guess_number;
static int solution1;
static int solution2;
static int solution3;
static int solution4;


/*
 * set_seed -- This function sets the seed value for pseudorandom
 * number generation based on the number the user types.
 * The input entered by the user is already stored in the string seed_str by the code in main.c.
 * This function should use the function sscanf to find the integer seed value from the 
 * string seed_str, then initialize the random number generator by calling srand with the integer
 * seed value. To be valid, exactly one integer must be entered by the user, anything else is invalid. 
 * INPUTS: seed_str -- a string (array of characters) entered by the user, containing the random seed
 * OUTPUTS: none
 * RETURN VALUE: 0 if the given string is invalid (string contains anything
 *               other than a single integer), or 1 if string is valid (contains one integer)
 * SIDE EFFECTS: initializes pseudo-random number generation using the function srand. Prints "set_seed: invalid seed\n"
 *               if string is invalid. Prints nothing if it is valid.
 */
int
set_seed (const char seed_str[])
{

	// Declare variable to hold seed
	int seed;
	// Declare variable to hold number of items returned sscanf()
	int numOfItems;	
	// Array of char to hold non integers entered
	char post[2];	
	// sscanf statement reads the integer into seed. 
	numOfItems = sscanf (seed_str, "%d%1s", &seed, post);

	// srand statement to set the seed
	srand(seed);
	// Check if sscanf returns only 1 item
	if(numOfItems == 1)
		return 1;
	else
	{
		// If sscanf returned more than 1 item, print invalid seed
		printf("set_seed: invalid seed\n");
		return 0;
	}
}


/*
 * start_game -- This function is called by main.c after set_seed but before the user makes guesses.
 *               This function creates the four solution numbers using the approach
 *               described in the wiki specification (using rand())
 *               The four solution numbers should be stored in the static variables defined above. 
 *               The values at the pointers should also be set to the solution numbers.
 *               The guess_number should be initialized to 1 (to indicate the first guess)
 * INPUTS: none
 * OUTPUTS: *one -- the first solution value (between 1 and 8)
 *          *two -- the second solution value (between 1 and 8)
 *          *three -- the third solution value (between 1 and 8)
 *          *four -- the fourth solution value (between 1 and 8)
 * RETURN VALUE: none
 * SIDE EFFECTS: records the solution in the static solution variables for use by make_guess, set guess_number
 */
void
start_game (int* one, int* two, int* three, int* four)
{
    //your code here

	// Set *one to random number between 1 and 8
	*one = (rand() % 8) + 1;
	// Set *two to random number between 1 and 8	
	*two = (rand() % 8) + 1;
	// Set *three to random number between 1 and 8	
	*three = (rand() % 8) + 1;
	// Set *four to random number between 1 and 8	
	*four = (rand() % 8) + 1;	
    
	// Set solution1 to *one
	solution1 = *one;
	// Set solution2 to *two			
	solution2 = *two;
	// Set solution3 to *three			
	solution3 = *three;
	// Set solution4 to *four			
	solution4 = *four;			
	
	// Initialize guess_number to 0
	guess_number = 0;			

}

/*
 * make_guess -- This function is called by main.c after the user types in a guess.
 *               The guess is stored in the string guess_str. 
 *               The function must calculate the number of perfect and misplaced matches
 *               for a guess, given the solution recorded earlier by start_game
 *               The guess must be valid (contain only 4 integers, within the range 1-8). If it is valid
 *               the number of correct and incorrect matches should be printed, using the following format
 *               "With guess %d, you got %d perfect matches and %d misplaced matches.\n"
 *               If valid, the guess_number should be incremented.
 *               If invalid, the error message "make_guess: invalid guess\n" should be printed and 0 returned.
 *               For an invalid guess, the guess_number is not incremented.
 * INPUTS: guess_str -- a string consisting of the guess typed by the user
 * OUTPUTS: the following are only valid if the function returns 1 (A valid guess)
 *          *one -- the first guess value (between 1 and 8)
 *          *two -- the second guess value (between 1 and 8)
 *          *three -- the third guess value (between 1 and 8)
 *          *four -- the fourth color value (between 1 and 8)
 * RETURN VALUE: 1 if the guess string is valid (the guess contains exactly four
 *               numbers between 1 and 8), or 0 if it is invalid
 * SIDE EFFECTS: prints (using printf) the number of matches found and increments guess_number(valid guess) 
 *               or an error message (invalid guess)
 *               (NOTE: the output format MUST MATCH EXACTLY, check the wiki writeup)
 */
int
make_guess (const char guess_str[], int* one, int* two, 
	    int* three, int* four)
{

	// Array to hold extra characters entered
	char post[2];	
	// Declare variables to hold guess		
	int w, x, y, z;	
	// Declare variable to hold number of items returned from sscanf()		
	int numOfItems;		
	// Declare and initialize variable to hold number of perfect guesses	
	int numOfPerfect = 0;
	// Declare and initialize variable to hold number of misplaced guesses	
	int numOfMisplaced = 0;	
	// Declare and initialize flags to determine guesses that haved been paired
	int soln1Found = 0, soln2Found = 0, soln3Found = 0, soln4Found = 0;
	// sscanf() to get guess integers
	numOfItems = sscanf (guess_str, "%d%d%d%d%1s", &w, &x, &y, &z, post);	

	// Check if number of items entered is not 4	
	if(numOfItems != 4)
	{
		printf("make_guess: invalid guess\n");
		return 0;
	}
	// Check if any of the numbers entered are not in the correct range
	else if(w < 1 || w > 8)
	{
		// If any of the guess numbers are not in the correct range, print invalid guess
		printf("make_guess: invalid guess\n");
		return 0;
	}
	else if(x < 1 || x > 8)
	{
		printf("make_guess: invalid guess\n");
		return 0;
	}
	else if(y < 1 || y > 8)
	{
		printf("make_guess: invalid guess\n");
		return 0;
	}
	else if(z < 1 || z > 8)
	{
		printf("make_guess: invalid guess\n");
		return 0;
	}
	else
	{
		// Set function parameters to equal the guess
		*one = w;
		*two = x;
		*three = y;
		*four = z;
		// Increment guess_number
		guess_number = guess_number + 1;
		// Check for perfect matches first
		if(w == solution1)
		{
			// If guess is a perfect match, increment numOfPerfect
			numOfPerfect = numOfPerfect + 1;
			// If guess is a perfect match, set solution flag to 1
			soln1Found = 1;
		}
		if(x == solution2)
		{
			numOfPerfect = numOfPerfect + 1;
			soln2Found = 1;
		}
		if(y == solution3)
		{
			numOfPerfect = numOfPerfect + 1;
			soln3Found = 1;
		}
		if(z == solution4)
		{
			numOfPerfect = numOfPerfect + 1;
			soln4Found = 1;
		}

		// Check for misplaced matches by comparing first guess number to other solution numbers
		// Also, check solution flags to make sure solutions have not been paired yet
		if(w == solution2 && soln2Found == 0 && soln1Found == 0)
		{
			// If guess is a misplaced match, increment numOfMisplaced
			numOfMisplaced = numOfMisplaced + 1;
			// Set solution flag to 1
			soln2Found = 1;
		}
		else if(w == solution3 && soln3Found == 0 && soln1Found == 0)
		{
			numOfMisplaced = numOfMisplaced + 1;
			soln3Found = 1;
		}
		else if(w == solution4 && soln4Found == 0 && soln1Found == 0)
		{
			numOfMisplaced = numOfMisplaced + 1;
			soln4Found = 1;
		}

		// Check for misplaced matches by comparing second guess number to other solution numbers
		// Also, check solution flags to make sure solutions have not been paired yet
		if(x == solution1 && soln1Found == 0 && soln2Found == 0)
		{
			// If guess is a misplaced match, increment numOfMisplaced
			numOfMisplaced = numOfMisplaced + 1;
			// Set solution flag to 1
			soln1Found = 1;
		}
		else if(x == solution3 && soln3Found == 0 && soln2Found == 0)
		{
			numOfMisplaced = numOfMisplaced + 1;
			soln3Found = 1;
		}
		else if(x == solution4 && soln4Found == 0 && soln2Found == 0)
		{
			numOfMisplaced = numOfMisplaced + 1;
			soln4Found = 1;
		}

		// Check for misplaced matches by comparing third guess number to other solution numbers
		// Also, check solution flags to make sure solutions have not been paired yet
		if(y == solution1 && soln1Found == 0)
		{
			// If guess is a misplaced match, increment numOfMisplaced
			numOfMisplaced = numOfMisplaced + 1;
			// Set solution flag to 1
			soln1Found = 1;
		}
		else if(y == solution2 && soln2Found == 0)
		{
			numOfMisplaced = numOfMisplaced + 1;
			soln2Found = 1;
		}
		else if(y == solution4 && soln4Found == 0)
		{
			numOfMisplaced = numOfMisplaced + 1;
			soln4Found = 1;
		}

		// Check for misplaced matches by comparing fourth guess number to other solution numbers
		// Also, check solution flags to make sure solutions have not been paired yet
		if(z == solution1 && soln1Found == 0)
		{
			// If guess is a misplaced match, increment numOfMisplaced
			numOfMisplaced = numOfMisplaced + 1;
			// Set solution flag to 1
			soln1Found = 1;
		}
		else if(z == solution2 && soln2Found == 0)
		{
			numOfMisplaced = numOfMisplaced + 1;
			soln2Found = 1;
		}
		else if(z == solution3 && soln3Found == 0)
		{
			numOfMisplaced = numOfMisplaced + 1;
			soln3Found = 1;
		}
		// Print guess number, number of perfect matches, and number of misplaced matches.
		printf("With guess %d, you got %d perfect matches and %d misplaced matches.\n", guess_number, numOfPerfect, numOfMisplaced);
		return 1;
	}

}



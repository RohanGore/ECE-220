#include "sudoku.h"

//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------


/*
 * INTRO PARAGRAPH
 * -------------------------------------------------------------------------------------------------------------------------------------
 * This program implements a sudoku solver.  6 functions are used, is_val_in_row, is_val_in_col, is_val_in_3x3_zone, find_unused_cells,
 * is_valid, and solve_sudoku.  is_val_in_row checks if a value is valid in the current row.  is_val_in_col checks if a value is valid
 * in the current column.  is_val_in_3x3_zone checks if a value is valid in the current 3x3 zone.  find_unused_cells finds any cells 
 * that currently contain 0.  is_valid checks if a value can be placed at a certain position in the grid.  solve_sudoku solves the 
 * sudoku using recursive backtracking.
 */


// You are free to declare any private functions if needed.

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

	assert(i>=0 && i<9);

	// BEG TODO
	// Loop through 9 columns while keeping row constant
	for(int j = 0; j < 9; j++)
	{
		// If the value already exists in the row, return 1
		if(val == sudoku[i][j])
			return 1;
	}
  	return 0;
	// END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

	assert(j>=0 && j<9);

	// BEG TODO
	// Loop through 9 rows while keeping column constant
	for(int i = 0; i < 9; i++)
	{
		// If the value already exists in the column, return 1
		if(val == sudoku[i][j])
			return 1;
	}
	return 0;
	// END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
   
	assert(i>=0 && i<9);
	// BEG TODO
	// Get the starting row index for the start of the corresponding 3x3 zone
	int rowStart = i - (i%3);
	// Get the starting column index for the start of the corresponding 3x3 zone
	int colStart = j - (j%3);
	// Loop through 3 rows
	for(int row = 0; row < 3; row++)
	{
		// Loop through 3 columns
		for(int col = 0; col < 3; col++)
		{
			// If the value already exists in the 3x3 zone, return 1
			if(sudoku[row+rowStart][col+colStart] == val)
				return 1;
		}
	}
	return 0;
	// END TODO
}

// Function to find all cells in the grid that are 0, using reference parameters row and column
int find_unused_cells(int sudoku[9][9]/*, int *row, int *col*/)
{
	for(int row=0; row<9; row++)
	{
		for(int col=0; col<9; col++)
		{
			// Check if grid has any cells that are 0 left and return 1 if there are
			if(sudoku[row][col]==0)
				return 1;
				
		}
	}
	// Returns 0 if no cells that are 0 left
	return 0;
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

	assert(i>=0 && i<9 && j>=0 && j<9);

	// BEG TODO
	// Check if value already exists in either the row, column, or 3x3 box
	if(is_val_in_row(val, i, sudoku) || is_val_in_col(val, j, sudoku) || is_val_in_3x3_zone(val, i, j, sudoku))
		// If the value does exist in either the row, column, or 3x3 box, return 0
		return 0;

	return 1;
	// END TODO
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {

	// BEG TODO.
	int row = 0, col = 0;
	// Call find_unused_cells function to find if there are any cells with 0
	if (find_unused_cells(sudoku)==0)
		return 1;
	// Loop through every possible number from 1 to 9
	for (int val = 1; val <= 9; val++ )
	{
		// Check if current number is valid
		if (is_val_valid(val, row, col, sudoku))
		{
			// If the number is valid, set the current cell to that number
			sudoku[row][col] = val;
			// Recursive Call
			if (solve_sudoku(sudoku))
				
				return 1;
			//Set cell back to 0 to start backtracking
			sudoku[row][col] = 0;
		}
	}
	return 0;
	// END TODO.
}

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}






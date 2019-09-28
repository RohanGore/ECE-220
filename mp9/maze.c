#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

/*
 * INTRO PARAGRAPH
 * -------------------------------------------------------------------------------------------------------------------------------------
 * This program implements a maze solver.  4 functions are used.  createMaze() creates a maze structure and allocates memory to it
 * destroyMaze() frees all memory allocated to a maze structure.  printMaze() prints the maze in a readable format
 * solveMazeDFS() solves the maze using depth first search and recursive backtracking to solve a maze
 */

/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None 
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
    // Your code here. Make sure to replace following line with your own code.
 	FILE *f;
	f = fopen(fileName, "r");
	if (f == NULL)
	{	 
		printf("file can't be opened");
		return NULL;
	}
	maze_t * maze;
	int width, height;
	//Allocate memory to maze struct
	maze = (maze_t *)malloc(sizeof(maze_t));
	int i, j;
		
	if(maze != NULL)
	{	
		//Scan file for width and height
		fscanf(f, "%d %d", &width, &height);
		maze->width = width;
		maze->height = height;
		//printf("%d %d", maze->width, maze->height);
		
		//Initialize Pointer Array
		maze->cells = malloc((height+1) * sizeof(char *));
		int k;
		for (k = 0; k <= height; k++)
		{
			maze->cells[k] = malloc(width * sizeof(char));
		}
		// Delare char variable to hold character read from file
		char index;
		//Loop through every row
		for(i = 0; i <= maze->height; i++)
		{
			// Loop through every column
			for(j = 0; j <= maze->width; j++)
			{
				// Skip first line of file
				if(i != 0)
				{
					// Read character from file
					index = fgetc(f);
					// Skip newline characters
					if(index == '\n')
						continue;
					//Copy character to cells array
					maze->cells[i-1][j-1] = index;
					if(index == 'S')
					{
						//Find location of Start in maze
						maze->startRow = i-1;
						maze->startColumn = j-1;
					}
					if(index == 'E')
					{
						//Find location of End in maze 
						maze->endRow = i-1;
						maze->endColumn = j-1;	
					}
				}
			}
		}

	}
	fclose(f);
	return maze;
}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information 
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
    // Your code here.
	// Check if maze is has memory allocated
	if(maze != NULL)
	{
		// Declare loop variable
		int k;
		// Loop through every rows
		for (k = 0; k<= maze->height; k++){
			// Free memory allocated to each row
			free(maze->cells[k]);
		}
		// Free memory allocated to the cells array
		free(maze->cells);
		// Free memory allocated to the maze
		free(maze);
	}
}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information 
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
    // Your code here.
	int i, j;
	//Loop throught every row	
	for(i=0; i<=maze->height; i++)
	{
		//Loop through every column
		for(j=0; j<=maze->width; j++)
		{
			//Print character at location in array		
			printf("%c", maze->cells[i][j]);
		}
		//Move to next line after one row
		printf("\n");
	}
}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */ 
int solveMazeDFS(maze_t * maze, int col, int row)
{
    // Your code here. Make sure to replace following line with your own code.

	// check if the value at the cell is empty or 
	// starting char 'S'
	if(maze->cells[row][col] != 'S')
	{
		// if the cell is not the start, update the value to '*'
		maze->cells[row][col] = '*';
	}
	// Check cell under current cell
	if(maze->cells[row+1][col] == ' ' || maze->cells[row+1][col] == 'E')
	{
		// If cell under current cell is end, return 1
		if(maze->cells[row+1][col] == 'E')
			return 1;
		else
			// Otherwise recursive call to cell under current
			return solveMazeDFS(maze, col, row+1);
	}
	// Check cell right of current cell
	else if(maze->cells[row][col+1] == ' ' || maze->cells[row][col+1] == 'E')
	{
		// If cell right of current cell is end, return 1
		if(maze->cells[row][col+1] == 'E')
			return 1;
		else
			// Otherwise recursive call to cell right of current
			return solveMazeDFS(maze, col+1, row);
	}
	// Check cell above current cell
	else if(maze->cells[row-1][col] == ' ' || maze->cells[row-1][col] == 'E')
	{
		// If cell above current cell is end, return 1
		if(maze->cells[row-1][col] == 'E')
			return 1;
		else
			// Otherwise recursive call to cell above current
			return solveMazeDFS(maze, col, row-1);
	}
	// Check cell left of current cell
	else if(maze->cells[row][col-1] == ' ' || maze->cells[row][col-1] == 'E')
	{
		// If cell left of current cell is end, return 1
		if(maze->cells[row][col-1] == 'E')
			return 1;
		else
			// Otherwise recursive call to cell above current
			return solveMazeDFS(maze, col-1, row);

	}
	else
	{
		maze->cells[row][col] = '~';	// If none of the spaces around work, mark cell as visited then backtrack
		if(maze->cells[row+1][col] == '*')
			return solveMazeDFS(maze, col, row+1);
		else if(maze->cells[row][col+1] == '*')
			return solveMazeDFS(maze, col+1, row);
		else if(maze->cells[row-1][col] == '*')
			return solveMazeDFS(maze, col, row-1);
		else if(maze->cells[row][col-1] == '*')
			return solveMazeDFS(maze, col-1, row);
	}
	return 0;
}

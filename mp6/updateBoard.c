/*
 * INTRO PARAGRAPH
 * -------------------------------------------------------------------------------------------------------------------------------------
 * This program implements Conway's game of Life.  3 functions are used to, countLiveNeighbor, updateBoard, and aliveStable.
 * countLiveNeighbor counts and returns the number of alive cells that are neighboring the current cell being tested.  updateBoard
 * calls countLiveNeighbor and updates the game board to the next generation.  aliveStable checks if there were any changes to the board
 * after each generation and returns 1 if there were no changes and 0 if there were changes.
 */


/*
 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */

int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){
	int numOfAlive = 0;
	if(row==0 && col==0) // Check if current cell is in top left corner
	{
		if(board[(row*boardColSize+col)+1] == 1)		// Check right neighbor
			numOfAlive = numOfAlive + 1;
		if(board[(row*boardColSize+col)+boardColSize] == 1)	// Check bottom neighbor
			numOfAlive = numOfAlive + 1;
		if(board[(row*boardColSize+col)+boardColSize+1] == 1)	// Check bottom right neighbor
			numOfAlive = numOfAlive + 1;
	}
	else if(row==0 && col==boardColSize-1) // Check if current cell is in top right corner
	{
		if(board[(row*boardColSize+col)-1] == 1)		// Check left neighbor
			numOfAlive = numOfAlive + 1;
		if(board[(row*boardColSize+col)+boardColSize-1] == 1)	// Check bottom left neighbor
			numOfAlive = numOfAlive + 1;
		if(board[(row*boardColSize+col)+boardColSize] == 1)	// Check bottom neighbor
			numOfAlive = numOfAlive + 1;		
	}
	else if(row==boardRowSize-1 && col==0) // Check if current cell is in if bottom left corner
	{
		if(board[(row*boardColSize+col)-boardColSize] == 1)	// Check top neighbor
			numOfAlive = numOfAlive + 1;
		if(board[(row*boardColSize+col)-boardColSize+1] == 1)	// Check top right neighbor
			numOfAlive = numOfAlive + 1;
		if(board[(row*boardColSize+col)+1] == 1)		// Check right neighbor
			numOfAlive = numOfAlive + 1;
	}
	else if(row==boardRowSize-1 && col==boardColSize-1) // Check if current cell is in bottom right corner
	{
		if(board[(row*boardColSize+col)-boardColSize-1] == 1)	// Check top left neighbor
			numOfAlive = numOfAlive + 1;		
		if(board[(row*boardColSize+col)-boardColSize] == 1)	// Check top neighbor
			numOfAlive = numOfAlive + 1;
		if(board[(row*boardColSize+col)-1] == 1)		// Check left neighbor
			numOfAlive = numOfAlive + 1;
	}
	else if(row!=0 && row!=boardRowSize-1 && col==0) // Check if current cell is in left column but not corners
	{
		if(board[(row*boardColSize+col)-boardColSize] == 1)	// Check top neighbor
			numOfAlive = numOfAlive + 1;
		if(board[(row*boardColSize+col)-boardColSize+1] == 1)	// Check top right neighbor
			numOfAlive = numOfAlive + 1;
		if(board[(row*boardColSize+col)+1] == 1)		// Check right neighbor
			numOfAlive = numOfAlive + 1;
		if(board[(row*boardColSize+col)+boardColSize] == 1)	// Check bottom neighbor
			numOfAlive = numOfAlive + 1;
		if(board[(row*boardColSize+col)+boardColSize+1] == 1)	// Check bottom right neighbor
			numOfAlive = numOfAlive + 1;
	}
	else if(row==0 && col!=0 && col!=boardColSize-1) // Check if current cell is in top row but not corners
	{
		if(board[(row*boardColSize+col)-1] == 1)		// Check left neighbor
			numOfAlive = numOfAlive + 1;
		if(board[(row*boardColSize+col)+1] == 1)		// Check right neighbor
			numOfAlive = numOfAlive + 1;
		if(board[(row*boardColSize+col)+boardColSize-1] == 1)	// Check bottom left neighbor
			numOfAlive = numOfAlive + 1;
		if(board[(row*boardColSize+col)+boardColSize] == 1)	// Check bottom neighbor
			numOfAlive = numOfAlive + 1;
		if(board[(row*boardColSize+col)+boardColSize+1] == 1)	// Check bottom right neighbor
			numOfAlive = numOfAlive + 1;
	}
	else if(row!=0 && row!=boardRowSize-1 && col==boardColSize-1) // Check if current cell is in right column but not corners
	{
		if(board[(row*boardColSize+col)-boardColSize-1] == 1)	// Check top left neighbor
			numOfAlive = numOfAlive + 1;
		if(board[(row*boardColSize+col)-boardColSize] == 1)	// Check top neighbor
			numOfAlive = numOfAlive + 1;
		if(board[(row*boardColSize+col)-1] == 1)		// Check left neighbor
			numOfAlive = numOfAlive + 1;
		if(board[(row*boardColSize+col)+boardColSize-1] == 1)	// Check bottom left neighbor
			numOfAlive = numOfAlive + 1;
		if(board[(row*boardColSize+col)+boardColSize] == 1)	// Check bottom neighbor
			numOfAlive = numOfAlive + 1;
	}
	else if(row==boardRowSize-1 && col!=0 && col!=boardColSize-1) // Check if current cell is in bottom row but not corners
	{
		if(board[(row*boardColSize+col)-boardColSize-1] == 1)	// Check top left neighbor
			numOfAlive = numOfAlive + 1;
		if(board[(row*boardColSize+col)-boardColSize] == 1)	// Check top neighbor
			numOfAlive = numOfAlive + 1;
		if(board[(row*boardColSize+col)-boardColSize+1] == 1)	// Check top right neighbor
			numOfAlive = numOfAlive + 1;
		if(board[(row*boardColSize+col)-1] == 1)		// Check left neighbor
			numOfAlive = numOfAlive + 1;
		if(board[(row*boardColSize+col)+1] == 1)		// Check right neighbor
			numOfAlive = numOfAlive + 1;
	}
	else // Else current cell is in middle of board and check all possible neighboring cells
	{
		if(board[(row*boardColSize+col)-boardColSize-1] == 1)	// Check top left neighbor
			numOfAlive = numOfAlive + 1;
		if(board[(row*boardColSize+col)-boardColSize] == 1)	// Check top neighbor
			numOfAlive = numOfAlive + 1;
		if(board[(row*boardColSize+col)-boardColSize+1] == 1)	// Check top right neighbor
			numOfAlive = numOfAlive + 1;
		if(board[(row*boardColSize+col)-1] == 1)		// Check left neighbor
			numOfAlive = numOfAlive + 1;
		if(board[(row*boardColSize+col)+1] == 1)		// Check right neighbor
			numOfAlive = numOfAlive + 1;
		if(board[(row*boardColSize+col)+boardColSize-1] == 1)	// Check bottom left neighbor
			numOfAlive = numOfAlive + 1;
		if(board[(row*boardColSize+col)+boardColSize] == 1)	// Check bottom neighbor
			numOfAlive = numOfAlive + 1;
		if(board[(row*boardColSize+col)+boardColSize+1] == 1)	// Check bottom right neighbor
			numOfAlive = numOfAlive + 1;
	}
	return numOfAlive;
}
/*
 * Update the game board to the next step.
 * Input: 
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */
void updateBoard(int* board, int boardRowSize, int boardColSize) {
	int count;	// Declare variable to hold number of alive neighbors
	int temp[boardRowSize * boardColSize];	// Declare temporary game board with size equal to the game board size
	for(int i = 0; i < boardRowSize; i++)
	{
		for(int j = 0; j < boardColSize; j++)
		{
			temp[i * boardColSize + j] = board[i * boardColSize + j];	// Copy the game board into the temporary game board
		}
	}

	for(int row = 0; row < boardRowSize; row++) // Loop through each row
	{
		for(int column = 0; column < boardColSize; column++) // Loop through each column
		{
			count = countLiveNeighbor(board, boardRowSize, boardColSize, row, column);
			if(board[row*boardColSize+column]==0 && count==3) // Check if cell is dead and if 3 live neighbors
				temp[row*boardColSize+column]=1;
			else if(board[row*boardColSize+column]==1 && count<2) // Check if cell is alive and if less than 2 live neighbors
				temp[row*boardColSize+column]=0;
			else if(board[row*boardColSize+column]==1&&(count==2||count==3)) // Check if cell is alive and if 2 or 3 live neighbors
				temp[row*boardColSize+column]=1;
			else if(board[row*boardColSize+column]==1 && count>3) // Check if cell is alive and if more than 3 live neighbors
				temp[row*boardColSize+column]=0;
		}
	}

	for(int i = 0; i < boardRowSize; i++)
	{
		for(int j = 0; j < boardColSize; j++)
		{
			board[i * boardColSize + j] = temp[i * boardColSize + j];	// Copy the updated temporary game board into the game board
		}
	}
	
}

/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with 
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */ 
int aliveStable(int* board, int boardRowSize, int boardColSize){
	int count, stable = 1;
	for(int row = 0; row < boardRowSize; row++) // Check every row
	{
		for(int column = 0; column < boardColSize; column++) // Check every column
		{
			count = countLiveNeighbor(board, boardRowSize, boardColSize, row, column); // Call countLiveNeighbor to get number of alive neighbors
			if(board[row*boardColSize+column] == 1 && count < 2) // Check if live cell dies
			{
				stable = 0;
				break;
			}
			else if(board[row*boardColSize+column]==1 && count>3) // Check if live cell dies
			{
				stable=0;
				break;
			}
		}
	}
	return stable;
}

				
				
			


#include "game.h"


/*
 * INTRO PARAGRAPH
 * -------------------------------------------------------------------------------------------------------------------------------------
 * This program implements the game 2048.  8 functions are used.  make_game() creates a game structure and allocates memory to it
 * remake_game() frees memory used by a game structure and reinitializes all values in the structure.  get_cell() returns a pointer 
 * to a specific cell in a game structure.  move_w() slides the cells up. move_s() slides the cells down. move_a() slides the 
 * cells left.  move_d() slides the cells right.  legal_move_check() checks if there are any legal moves that can be made
 * in the current game state
 */

game * make_game(int rows, int cols)
/*! Create an instance of a game structure with the given number of rows
    and columns, initializing elements to -1 and return a pointer
    to it. (See game.h for the specification for the game data structure) 
    The needed memory should be dynamically allocated with the malloc family
    of functions.
*/
{
    //Dynamically allocate memory for game and cells (DO NOT modify this)
    game * mygame = malloc(sizeof(game));
    mygame->cells = malloc(rows*cols*sizeof(cell));

    //YOUR CODE STARTS HERE:  Initialize all other variables in game struct

	mygame->rows = rows;	// Set number of rows in game to given value
	mygame->cols = cols;	// Set number of columns in game to given value
	mygame->score = 0;	// Initialize score to 0
	int i, j;	// Declare loop variables
	for(i = 0; i < mygame->cols; i++)	// Loop through every column
	{
		for(j = 0; j < mygame->rows; j++)	// Loop through every row
		{
			mygame->cells[j * cols + i] = -1;	// Initialize every cell to -1
		}
	}

    return mygame;	// Return the pointer to the game
}

void remake_game(game ** _cur_game_ptr,int new_rows,int new_cols)
/*! Given a game structure that is passed by reference, change the
	game structure to have the given number of rows and columns. Initialize
	the score and all elements in the cells to -1. Make sure that any 
	memory previously allocated is not lost in this function.	
*/
{
	/*Frees dynamically allocated memory used by cells in previous game,
	 then dynamically allocates memory for cells in new game.  DO NOT MODIFY.*/
	free((*_cur_game_ptr)->cells);
	(*_cur_game_ptr)->cells = malloc(new_rows*new_cols*sizeof(cell));

	 //YOUR CODE STARTS HERE:  Re-initialize all other variables in game struct

	(*_cur_game_ptr)->rows = new_rows;	// Re-initialize number of rows
	(*_cur_game_ptr)->cols = new_cols;	// Re-initialize number of columns
	(*_cur_game_ptr)->score = 0;	// Re-initialize score to 0
	int i, j;	// Declare loop variables
	for(i = 0; i < (*_cur_game_ptr)->cols; i++)	// Loop through every column
	{
		for(j = 0; j < (*_cur_game_ptr)->rows; j++)	// Loop through every row
		{
			*get_cell(*_cur_game_ptr, j, i) = -1;	// Initialize every cell to -1
		}
	}

	return;	
}

void destroy_game(game * cur_game)
/*! Deallocate any memory acquired with malloc associated with the given game instance.
    This includes any substructures the game data structure contains. Do not modify this function.*/
{
    free(cur_game->cells);
    free(cur_game);
    cur_game = NULL;
    return;
}

cell * get_cell(game * cur_game, int row, int col)
/*! Given a game, a row, and a column, return a pointer to the corresponding
    cell on the game. (See game.h for game data structure specification)
    This function should be handy for accessing game cells. Return NULL
	if the row and col coordinates do not exist.
*/
{
    //YOUR CODE STARTS HERE
	
	cell * newCell;		// Declare a pointer to a cell
	if(row < cur_game->rows || row >= 0 || col < cur_game->cols || col >= 0)	// Check if the given row and column are in the range
	{
		newCell = &cur_game->cells[row * cur_game->cols + col];	// Set cell pointer to point at the new cell
		return newCell;		// Return newCell
	}
	else
		return NULL;
}

int move_w(game * cur_game)
/*!Slides all of the tiles in cur_game upwards. If a tile matches with the 
   one above it, the tiles are merged by adding their values together. When
   tiles merge, increase the score by the value of the new tile. A tile can 
   not merge twice in one turn. If sliding the tiles up does not cause any 
   cell to change value, w is an invalid move and return 0. Otherwise, return 1. 
*/
{
    //YOUR CODE STARTS HERE

	int i, j, k;	// Declare loop variables

	int change = 0;		// Declare variable to detect any change and initialize to 0

	for(j = 0; j < cur_game->cols; j++)	// Loop through every row
	{
		for(i = 0; i < cur_game->rows; i++)	// Loop through every column
		{
			if(*get_cell(cur_game, i, j) != -1)	// Check if current cell is not empty
			{
				for(k = i+1; k < cur_game->rows; k++)	// Loop through every column after i
				{
					if(*get_cell(cur_game, k, j) != -1)	// Check it next cell is not empty
					{
						if(*get_cell(cur_game, i, j) == *get_cell(cur_game, k, j))	// Check if current cell and next cell are equal
						{		
							*get_cell(cur_game, i, j) *= 2;		// If current cell and next cell are equal, double current cell	
							change = 1;		// Set change variable to 1
							cur_game->score = cur_game->score + *get_cell(cur_game, i, j);	// Change the score
							*get_cell(cur_game, k, j) = -1;		// Set the next cell to -1
						}
						break;
					}
				}
			}
		}
	}


	for(j = 0; j < cur_game->cols; j++)		// Loop through every row
	{
		for(i = 0; i < cur_game->rows; i++)	// Loop through every column
		{
			if(*get_cell(cur_game, i, j) != -1)	// Check if current cell is empty
			{
				for(k = 0; k < i; k++)			// Loop through every cell before current cell
				{
					if(*get_cell(cur_game, k, j) == -1)	// Check if cell before current cell is empty
						break;
				}
				if(k < i)
				{
					*get_cell(cur_game, k, j) = *get_cell(cur_game, i, j);	// Set cell before current cell equal to current cell
					change = 1;	// Set change variable to 1
					*get_cell(cur_game, i, j) = -1;		// Change current cell to -1
				}
			}
		}
	}

    return change;	// Return change variable
};

int move_s(game * cur_game) //slide down
{
    //YOUR CODE STARTS HERE

	int i, j, k;		// Declare loop variables

	int change = 0;		// Declare variable to detect any change and initialize to 0

	for(j = 0; j < cur_game->cols; j++)		// Loop through every row
	{
		for(i = 0; i < cur_game->rows; i++)	// Loop through every column
		{
			if(cur_game->cells[i * cur_game->cols + j] != -1)	// Check if current cell is empty
			{
				for(k = i+1; k < cur_game->rows; k++)			// Loop through every column after i
				{
					if(cur_game->cells[k * cur_game->cols + j] != -1)	// Check it next cell is not empty
					{
						if(cur_game->cells[i * cur_game->cols + j] == cur_game->cells[k * cur_game->cols + j])	// Check if current cell and next cell are equal
						{	
							cur_game->cells[i * cur_game->cols + j] *= 2;	// If current cell and next cell are equal, double current cell	
							change = 1;	// Set change variable to 1
							cur_game->score = cur_game->score + cur_game->cells[i * cur_game->cols + j];	// Change the score
							cur_game->cells[k * cur_game->cols + j] = -1;	// Set the next cell to -1
						}
						break;
					}
				}
			}
		}
	}

	for(j = 0; j < cur_game->cols; j++)	// Loop through every row
	{
		for(i = cur_game->rows - 1; i >= 0; i--)	// Loop through every column
		{
			if(cur_game->cells[i * cur_game->cols + j] != -1)	// Check if current cell is empty
			{
				for(k = cur_game->rows - 1; k > i; k--)			// Loop through every cell after current cell
				{
					if(cur_game->cells[k * cur_game->cols + j] == -1)	// Check if cell after current cell is empty
						break;
				}
				if(k > i)
				{
					cur_game->cells[k * cur_game->cols + j] = cur_game->cells[i * cur_game->cols + j];	// Set cell before current cell equal to current cell
					change = 1;	// Set change variable to 1
					cur_game->cells[i * cur_game->cols + j] = -1;	// Change current cell to -1
				}
			}
		}
	}

    return change;
};

int move_a(game * cur_game) //slide left
{
    //YOUR CODE STARTS HERE

	int i, j, k; 			// Declare loop variables

	int change = 0;			// Declare variable to detect any change and initialize to 0

	for(i = 0; i < cur_game->rows; i++)		// Loop through every column	
	{
		for(j = 0; j < cur_game->cols; j++)	// Loop through every row
		{
			if(cur_game->cells[i * cur_game->cols + j] != -1)	// Check if current cell is empty
			{
				for(k = j+1; k < cur_game->cols; k++)			// Loop through every cell before current cell
				{
					if(cur_game->cells[i * cur_game->cols + k] != -1)	// Check it next cell is not empty
					{
						if(cur_game->cells[i * cur_game->cols + j] == cur_game->cells[i * cur_game->cols + k])	// Check if current cell and next cell are equal
						{
							cur_game->cells[i * cur_game->cols + j] *= 2;	// If current cell and next cell are equal, double current cell	
							change = 1;	// Set change variable to 1
							cur_game->score = cur_game->score + cur_game->cells[i * cur_game->cols + j];		// Change the score
							cur_game->cells[i * cur_game->cols + k] = -1;	// Set the next cell to -1
						}
						break;
					}
				}
			}
		}
	}

	for(i = 0; i < cur_game->rows; i++)	// Loop through every column
	{
		for(j = 0; j < cur_game->cols; j++)	// Loop through every row
		{

			if(cur_game->cells[i * cur_game->cols + j] != -1)	// Check if current cell is empty
			{
				for(k = 0; k < j; k++)	// Loop through every cell before current cell
				{
					if(cur_game->cells[i * cur_game->cols + k] == -1)	// Check it previous cell is not empty
						break;
				}
				if(k < j)
				{
					cur_game->cells[i * cur_game->cols + k] = cur_game->cells[i * cur_game->cols + j];	// Set cell before current cell equal to current cell
					change = 1;	// Set change variable to 1
					cur_game->cells[i * cur_game->cols + j] = -1;	// Change current cell to -1
				}
			}
		}
	}

    return change;
};

int move_d(game * cur_game){ //slide to the right
    //YOUR CODE STARTS HERE

	int i, j, k; 	// Declare loop variables

	int change = 0;		// Declare variable to detect any change and initialize to 0

	for(i = 0; i < cur_game->rows; i++)	// Loop through every column
	{
		for(j = 0; j < cur_game->cols; j++)	// Loop through every row
		{
			if(cur_game->cells[i * cur_game->cols + j] != -1)	// Check if current cell is empty
			{
				for(k = j+1; k < cur_game->cols; k++)	// Loop through every cell before current cell
				{
					if(cur_game->cells[i * cur_game->cols + k] != -1)	// Check it next cell is not empty
					{
						if(cur_game->cells[i * cur_game->cols + j] == cur_game->cells[i * cur_game->cols + k])	// Check if current cell and next cell are equal
						{
							cur_game->cells[i * cur_game->cols + j] *= 2;	// If current cell and next cell are equal, double current cell	
							change = 1;										// Set change variable to 1
							cur_game->score = cur_game->score + cur_game->cells[i * cur_game->cols + j];	// Change the score
							cur_game->cells[i * cur_game->cols + k] = -1;	// Set the next cell to -1
						}
						break;
					}
				}
			}
		}
	}

	for(i = 0; i < cur_game->rows; i++)			// Loop through every column
	{
		for(j = cur_game->cols-1; j >= 0; j--)	// Loop through every row
		{

			if(cur_game->cells[i * cur_game->cols + j] != -1)	// Check if current cell is empty
			{
				for(k = cur_game->cols-1; k > j; k--)	// Loop through every cell before current cell
				{
					if(cur_game->cells[i * cur_game->cols + k] == -1)	// Check it previous cell is not empty
						break;
				}
				if(k > j)
				{
					cur_game->cells[i * cur_game->cols + k] = cur_game->cells[i * cur_game->cols + j];	// Set cell before current cell equal to current cell
					change = 1;	// Set change variable to 1
					cur_game->cells[i * cur_game->cols + j] = -1;	// Change current cell to -1
				}							
			}
		}
	}

    return change;
};

int legal_move_check(game * cur_game)
/*! Given the current game check if there are any legal moves on the board. There are
    no legal moves if sliding in any direction will not cause the game to change.
	Return 1 if there are possible legal moves, 0 if there are none.
 */
{
    //YOUR CODE STARTS HERE
	
	game * tempGame = make_game(cur_game->rows, cur_game->cols);	// Declare pointer to a temporary game

	int i, j;	// Declare loop variables

	for(i = 0; i < cur_game->rows; i++)		// Loop through every column
	{
		for(j = 0; j < cur_game->cols; j++)	// Loop through every row
		{
			*get_cell(tempGame, i, j) = *get_cell(cur_game, i, j);	// Set cell in tempGame to the cell in cur_game
		}
	}

	if(move_w(tempGame) == 0 && move_a(tempGame) == 0 && move_s(tempGame) == 0 && move_d(tempGame) == 0 )	// Check return values of move functions 
	{
		destroy_game(tempGame);		// Free memory used by tempGame
		return 0;	// Return 0 if no changes by any move functions
	}
	
	destroy_game(tempGame);			// Free memory used by tempGame
    return 1;		// Return 1
}


/*! code below is provided and should not be changed */

void rand_new_tile(game * cur_game)
/*! insert a new tile into a random empty cell. First call rand()%(rows*cols) to get a random value between 0 and (rows*cols)-1.
*/
{
	
	cell * cell_ptr;
    cell_ptr = 	cur_game->cells;
	
    if (cell_ptr == NULL){ 	
        printf("Bad Cell Pointer.\n");
        exit(0);
    }
	
	
	//check for an empty cell
	int emptycheck = 0;
	int i;
	
	for(i = 0; i < ((cur_game->rows)*(cur_game->cols)); i++){
		if ((*cell_ptr) == -1){
				emptycheck = 1;
				break;
		}		
        cell_ptr += 1;
	}
	if (emptycheck == 0){
		printf("Error: Trying to insert into no a board with no empty cell. The function rand_new_tile() should only be called after tiles have succesfully moved, meaning there should be at least 1 open spot.\n");
		exit(0);
	}
	
    int ind,row,col;
	int num;
    do{
		ind = rand()%((cur_game->rows)*(cur_game->cols));
		col = ind%(cur_game->cols);
		row = ind/cur_game->cols;
    } while ( *get_cell(cur_game, row, col) != -1);
        //*get_cell(cur_game, row, col) = 2;
	num = rand()%20;
	if(num <= 1){
		*get_cell(cur_game, row, col) = 4; // 1/10th chance
	}
	else{
		*get_cell(cur_game, row, col) = 2;// 9/10th chance
	}
}

int print_game(game * cur_game) 
{
    cell * cell_ptr;
    cell_ptr = 	cur_game->cells;

    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int i,j;
	
	printf("\n\n\nscore:%d\n",cur_game->score); 
	
	
	printf("\u2554"); // topleft box char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // top box char
	printf("\u2557\n"); //top right char 
	
	
    for(i = 0; i < rows; i++){
		printf("\u2551"); // side box char
        for(j = 0; j < cols; j++){
            if ((*cell_ptr) == -1 ) { //print asterisks
                printf(" **  "); 
            }
            else {
                switch( *cell_ptr ){ //print colored text
                    case 2:
                        printf("\x1b[1;31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4:
                        printf("\x1b[1;32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8:
                        printf("\x1b[1;33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 16:
                        printf("\x1b[1;34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 32:
                        printf("\x1b[1;35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 64:
                        printf("\x1b[1;36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 128:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 256:
                        printf("\x1b[32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 512:
                        printf("\x1b[33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 1024:
                        printf("\x1b[34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 2048:
                        printf("\x1b[35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4096:
                        printf("\x1b[36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8192:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
					default:
						printf("  X  ");

                }

            }
            cell_ptr++;
        }
	printf("\u2551\n"); //print right wall and newline
    }
	
	printf("\u255A"); // print bottom left char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // bottom char
	printf("\u255D\n"); //bottom right char
	
    return 0;
}

int process_turn(const char input_char, game* cur_game) //returns 1 if legal move is possible after input is processed
{ 
	int rows,cols;
	char buf[200];
	char garbage[2];
    int move_success = 0;
	
    switch ( input_char ) {
    case 'w':
        move_success = move_w(cur_game);
        break;
    case 'a':
        move_success = move_a(cur_game);
        break;
    case 's':
        move_success = move_s(cur_game);
        break;
    case 'd':
        move_success = move_d(cur_game);
        break;
    case 'q':
        destroy_game(cur_game);
        printf("\nQuitting..\n");
        return 0;
        break;
	case 'n':
		//get row and col input for new game
		dim_prompt: printf("NEW GAME: Enter dimensions (rows columns):");
		while (NULL == fgets(buf,200,stdin)) {
			printf("\nProgram Terminated.\n");
			return 0;
		}
		
		if (2 != sscanf(buf,"%d%d%1s",&rows,&cols,garbage) ||
		rows < 0 || cols < 0){
			printf("Invalid dimensions.\n");
			goto dim_prompt;
		} 
		
		remake_game(&cur_game,rows,cols);
		
		move_success = 1;
		
    default: //any other input
        printf("Invalid Input. Valid inputs are: w, a, s, d, q, n.\n");
    }

	
	
	
    if(move_success == 1){ //if movement happened, insert new tile and print the game.
         rand_new_tile(cur_game); 
		 print_game(cur_game);
    } 

    if( legal_move_check(cur_game) == 0){  //check if the newly spawned tile results in game over.
        printf("Game Over!\n");
        return 0;
    }
    return 1;
}

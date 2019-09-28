#include "sparsemat.h"

#include <stdio.h>
#include <stdlib.h>


/*
 * INTRO PARAGRAPH
 * -------------------------------------------------------------------------------------------------------------------------------------
 * This program implements the game a sparse matrix using a linked list.  7 functions are used.  load_tuples() opens an input file 
 * and loads the values to be stored in the sparse matrix. gv_tuples() returns a certain value in the linked list.  set_tuples() sets 
 * the element at row and col to value.  save_tuples() writes the sparse matrix to an output file.  add_tuples() adds two sparse matrices
 * together.  mult_tuples() multiplies two sparse matrices together.
 */


sp_tuples * load_tuples(char* input_file)
{
	FILE * f; // Make File pointer
	f = fopen(input_file, "r"); // Open the input file

	sp_tuples * newMat; // Declare pointer to sp_tuples structure
	newMat = (sp_tuples *)malloc(sizeof(sp_tuples)); // Allocate memory to the sp_tuples structure

	int m, n; // Declare variables to hold dimensions of matrix

	fscanf(f, "%d %d", &m, &n); // Read dimensions from input file
	newMat->m = m; // Set dimensions of matrix
	newMat->n = n; // Set dimensions of matrix
	newMat->tuples_head = NULL; // Set head of linked list to NULL

	int row, col; // Declare variables to hold index of value
	double value; // Declare variable to hold value

	while(fscanf(f, "%d %d %lf\n", &row, &col, &value) != EOF) // Loop through file reading each line until end of file
	{
		printf("%d %d %lf\n", row, col, value);
		set_tuples(newMat, row, col, value); // Call set_tuples function with values read from file
	}

	fclose(f); // Close file
	return newMat; // Return sp_tuples structure
}



double gv_tuples(sp_tuples * mat_t,int row,int col)

{
	sp_tuples_node * current = mat_t->tuples_head; // Make current node and set to head
	if(row >= mat_t->m || col >= mat_t->n) // Check if row and col are in range
		return 0;
	else
	{
		while(current != NULL) // Traverse linked list
		{
			if(row == current->row && col == current->col) // If value is found at current position, return value
				return current->value;
			else
				current = current->next; // Otherwise, set current to next node
		}
	}
	return 0;
}



void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{

	sp_tuples_node * current = mat_t->tuples_head; // Make current node and set to head
	sp_tuples_node * previous; // Make node to hold previous node

	sp_tuples_node * newNode; // Make node to hold new data
 
	sp_tuples_node * temp; // Make temporary node

	if(value == 0) // If value is 0, delete the node
	{
		temp = (sp_tuples_node*) malloc(sizeof(sp_tuples_node));
		if(current != NULL && current->value == value)
		{
			mat_t->tuples_head = current->next;
			free(current);
			return;
		}
		
		while(current != NULL && current->value != value)
		{
			previous = current;	
			current = temp->next;
		}
		
		if(current == NULL)
			return;

		previous->next = current->next;	
		mat_t->nz = mat_t->nz - 1;
	}		
	else
	{
		if(mat_t->tuples_head == NULL)	// If head is null, insert new node at the head
		{
			mat_t->tuples_head = (sp_tuples_node*) malloc(sizeof(sp_tuples_node));
			mat_t->tuples_head->row = row;
			mat_t->tuples_head->col = col;
			mat_t->tuples_head->value = value;
			mat_t->tuples_head->next = NULL;
			mat_t->nz = mat_t->nz + 1;
		}
		else if(row < mat_t->tuples_head->row || (row == mat_t->tuples_head->row && col < mat_t->tuples_head->col)) // If row or col less than head, insert before head
		{
			mat_t->tuples_head = (sp_tuples_node*) malloc(sizeof(sp_tuples_node));
			newNode = (sp_tuples_node*) malloc(sizeof(sp_tuples_node));
			newNode->row = row;
			newNode->col = col;
			newNode->value = value;
			newNode->next = mat_t->tuples_head;
			mat_t->tuples_head = newNode;
			mat_t->nz = mat_t->nz + 1;
		}		
		else if(mat_t->tuples_head->row == row && mat_t->tuples_head->col == col) // If row and col equal to head, overwrite head
		{
			mat_t->tuples_head->value = value;
		}
		else
		{
			while(current != NULL) // Otherwise, traverse the linked list
			{
				if(current->row == row && current->col == col) // If row and col, already in linked list, overwrite
				{
					current->value = value;
					break;
				}				
				previous = current;
				current = current->next;
				if(current == NULL) // If at the end of linked list, insert at the end of linked list
				{
					newNode = (sp_tuples_node*) malloc(sizeof(sp_tuples_node));
					previous->next = newNode;
					newNode->next = NULL;
				}
				else if(previous->row == row && previous->col < col) // If row is same and previous col is less than col
				{
					if(current->row > row || current->col > col) // If next col is greater than col, insert
					{
						newNode = (sp_tuples_node*) malloc(sizeof(sp_tuples_node));
						temp = current;
						current = newNode;
						newNode->next = temp;
						mat_t->nz = mat_t->nz + 1;
						free(temp);
						break;
					}
				}
				else if(previous->row < row) // If previous row is less than row
				{
					if(current->row > row || (current->row == row && current->col > col)) // If next row is greater than row or next row is equal to row and next col is greater than col, insert
					{
						newNode = (sp_tuples_node*) malloc(sizeof(sp_tuples_node));
						temp = current;
						current = newNode;
						newNode->next = temp;
						mat_t->nz = mat_t->nz + 1;
						free(temp);
						break;
					}
				}
			}
		}
	}
    return;
}



void save_tuples(char * file_name, sp_tuples * mat_t)
{
	FILE * f; // Make file pointer
	f = fopen(file_name, "w"); // Open output file for writing
	
	sp_tuples_node * current = mat_t->tuples_head; // Make current node and set to head
	fprintf(f, "%d %d\n", mat_t->m, mat_t->n); // Print to output file
	while(current != NULL) // Traverse linked list
	{
		fprintf(f, "%d %d %lf\n", current->row, current->col, current->value); // Write to output file
	}
	fclose(f); // Close output file

	return;
}



sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB)
{
	sp_tuples * retmat;
	retmat = (sp_tuples *)malloc(sizeof(sp_tuples));

	retmat->m = matA->m;
	retmat->n = matA->n;
	retmat->nz = 0;

	

	return retmat;
}



sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB){ 
    return NULL;

}


	
void destroy_tuples(sp_tuples * mat_t)
{
	free(mat_t);  // Free memory allocated to mat_t
    return;
}  







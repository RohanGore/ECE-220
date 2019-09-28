#include "vector.h"
#include <stdlib.h>


vector_t * createVector(int initialSize)
{
	vector_t * myvector = (vector_t *)malloc(sizeof(vector_t));
	myvector->array = malloc(initialSize*sizeof(int));
	
	myvector->size = 0;
	myvector->maxSize = initialSize;

	return myvector;
}

void destroyVector(vector_t * vector)
{
	free(vector->array);
	free(vector);
	vector = NULL;
}

void resize(vector_t * vector)
{
	vector->maxSize *= 2;
	vector->array = (int *)realloc(vector->array, vector->maxSize * 2 * sizeof(int));
}

void push_back(vector_t * vector, int element)
{
	
	if(vector->size == vector->maxSize)
		resize(vector);
	
	vector->array[vector->size] = element;
	vector->size++;	

}

int pop_back(vector_t * vector)
{

	if(vector->size == 0)
		return 0;

	vector->size--;
	return vector->array[vector->size];
	
}

int access(vector_t * vector, int index)
{

	if(index < 0 || index >= vector->size)
		return 0;

	return vector->array[index];

}


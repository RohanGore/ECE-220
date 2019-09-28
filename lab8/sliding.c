#include "sliding.h"
/*  Slide all values of array up
*/
void slide_up(int* my_array, int rows, int cols){
	
	int i, j, k;

	for(i = 0; i < cols; i++)
	{
		for(j = 0; j < rows; j++)
		{
			if(my_array[j * cols + i] != -1)
			{
				for(k = 0; k < j; k++)
				{
					if(my_array[k * cols + i] == -1)
						break;
				}
				if(k < j)
				{
					my_array[(k * cols) + i] = my_array[(j * cols) + i];
					my_array[j * cols + i] = -1;
				}
			}
			else
			{
				
			}
		}
	}
	return;
}

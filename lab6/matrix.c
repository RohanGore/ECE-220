/* Function matrix_multiply
 * matrixA, matrixB, and matrix C are matrices represented as
 * one-dimensional arrays in row-major order. This function must
 * preform matrix multiplication so that C=A*B. 
 * INPUT: matrixA, a one dimensional array of size m*k
 *        matrixB, a one dimensional double array of size k*n
 * OUTPUT: matrixC, a one dimensional double array of size m*n
 */
void matrix_multiply(double *matrixA,double *matrixB,double *matrixC,int m,int k,int n)
{
//YOUR CODE HERE
	// Declare variable to hold matrixC element value
	double sum;
	// Loop to loop through rows
	for(int i = 0; i < m; i++)
	{
		// Loop to loop through columns
		for(int j = 0; j < n; j++)
		{
			// Set sum to 0
			sum = 0;
			// Loop to loop through summation
			for(int l = 0; l < k; l++)
			{
				// Add product of matrixA and matrixB element multiplication to previous value of sum
				sum = sum + (matrixA[i*k + l] * matrixB[l*n + j]);
			}
			// Set matrixC element to equal sum
			matrixC[i*n + j] = sum;
		}
	}

}


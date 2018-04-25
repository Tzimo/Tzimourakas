#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "rand_matrix.h"

#define n 1000

double A[n][n];
double B[n][n];
double C[n][n];


int main(int argc, char * argv[])
{
	// Update progress
	printf("Initializing matrices...\n");
	
	// Iterators
	int i, j, k;

	// Create random matrices
	rand_matrix();

	// Update progress
	printf("Computing matrix product...\n");
	
	// Begin clock
	clock_t begin, end;
	double time_spent;
	begin = clock();

	// Compute matrix product
	
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			C[i][j] = 0;			
			for (k = 0; k < n; k++)
			{
				C[i][j] += A[i][k]*B[k][j];
			}
		}
	}

	// Stop clock
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Time spent computing matrix product: %lf\n",time_spent);
	
	return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <omp.h>
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
	int i, j, k, ii, kk;
	// Block sizes
	int ib = 20;
	int kb = 50;
	int n_loops = n;
	
	// Variables for data prefetching
	double a00, a01, a10, a11, a20, a21, a30, a31;

	// Parallization variables
	int nprocs = atoi(argv[1]);

	// Create random matrices
	rand_matrix();

	// Update progress
	printf("Computing matrix product...\n");
	
	// Begin clock
	clock_t begin, end;
	double time_spent;
	begin = clock();

	///// Compute matrix product
	omp_set_num_threads(nprocs);
	int sched = n_loops/(ib*nprocs);


	// Loop through first block
	#pragma omp parallel
	{
		#pragma omp for private(i,j,k,kk,ii,a00,a01,a10,a11,a20,a21,a30,a31) schedule(static,sched)
		for (ii = 0; ii < n_loops; ii += ib)
		{
			// Loop through second block
			for (kk = 0; kk < n_loops; kk += kb)
			{
				// Loop through columns iterating by 2
				for (j = 0; j < n_loops; j += 2)
				{
					// Loop through rows iterating by 4
					for (i = ii; i < ii + ib; i += 4)
					{
						// Check if it's the first time looping through the block
						// Set prefetching variables = 0 if true
						if (kk == 0)
							a00 = a01 = a10 = a11 = a20 = a21 = a30 = a31 = 0;

						// Else set prefetching variables equal to the 4x2 block of values
						// in the result matrix, C
						else
						{
							a00 = C[i][j];
							a01 = C[i][j+1];
							a10 = C[i+1][j];
							a11 = C[i+1][j+1];
							a20 = C[i+2][j];
							a21 = C[i+2][j+1];
							a30 = C[i+3][j];
							a31 = C[i+3][j+1];
						}
					
						// Loop through kb columns in the A matrix and rows in the B matrix
						// Uses the 4x2 block to multiply
						for (k = kk; k < kk + kb; k++)
						{
							a00 += A[i][k]*B[k][j];
							a01 += A[i][k]*B[k][j+1];
							a10 += A[i+1][k]*B[k][j];
							a11 += A[i+1][k]*B[k][j+1];
							a20 += A[i+2][k]*B[k][j];
							a21 += A[i+2][k]*B[k][j+1];
							a30 += A[i+3][k]*B[k][j];
							a31 += A[i+3][k]*B[k][j+1];
						}

						// Reassign the result matrix with the prefetched variables
						C[i][j] = a00;
						C[i][j+1] = a01;
    					C[i+1][j]= a10;
    					C[i+1][j+1] = a11;
    					C[i+2][j] = a20;
    					C[i+2][j+1] = a21;
						C[i+3][j] = a30;
						C[i+3][j+1] = a31;
					}
				}
			}
		}
	}

	// Stop clock
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Time spent computing matrix product: %lf\n",time_spent);

	return 0;
}

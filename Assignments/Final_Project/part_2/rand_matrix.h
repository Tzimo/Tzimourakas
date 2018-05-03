#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define n 1000
double A[n][n];
double B[n][n];
double C[n][n];

void rand_matrix()
{
	int i, j;
	srand ( time(NULL) );
	
	for (i = 0; i < n; i++)
	{		
		for (j = 0; j < n; j++)
		{
			A[i][j] = (double) rand() / RAND_MAX;
			B[i][j] = (double) rand() / RAND_MAX;
		}
	}
}

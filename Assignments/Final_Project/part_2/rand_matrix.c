#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "rand_matrix.h"

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

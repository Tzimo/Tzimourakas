// Michael Tzimourakas
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <lapacke.h>
#include "BC.h"
#include "Build_LHS.h"
#include "Build_RHS.h"
#include "output.h"
#include "conductivity.h"
#include "Source.h"
#include "BuildMatrix.h"

double **BuildMatrix(int Nrows, int Ncols){

	int n;
	double **A = (double **) calloc(Nrows,sizeof(double*));
	A[0] = (double*) calloc(Nrows*Ncols, sizeof(double));

	for(n=1;n<Nrows;++n){
		A[n] = A[n-1]+ Ncols;
	}
	return A;
}
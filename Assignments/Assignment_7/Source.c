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


double Source(int x, int y, int problem_index){

if (problem_index == 1)
	return 0;

else if (problem_index == 2)
	return 2*(y*(1-y) + x*(1-x));

else if (problem_index == 3)
	return exp(-50*sqrt((pow(x-0.5,2) + pow(y-0.5,2))));

else if (problem_index == 4)
	if (x < 0.1)
		return 1;
	else 
		return 0;

else if (problem_index == 5)
	if (x > 0.01 && x < 0.015 && y > 0.01 && y < 0.015)
		return 1600000;
	else
		return 0;
}
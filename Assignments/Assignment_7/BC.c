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


double BC(int x, int y, int problem_index){

if (problem_index == 1)
	return x;

else if (problem_index == 2 || problem_index == 3 || problem_index == 4)
	return 0;

else if (problem_index == 5)
	return 70;

}
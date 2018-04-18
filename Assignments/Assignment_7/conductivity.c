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


double conductivity(int x, int y,int problem_index){
if ( problem_index == 1 || problem_index == 2 || problem_index == 3)
		return 1;

else if (problem_index == 4 )
	if (x > 0.5)
		return 20;
	else 
		return 1;

else if (problem_index == 5)
	if (x > 0.01 && x < 0.015 && y > 0.01 && y < 0.015)
		return 167;
	else
		return 157;

}
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



/*double **BuildMatrix(int Nrows, int Ncols){

	int n;
	double **A = (double **) calloc(Nrows,sizeof(double*));
	A[0] = (double*) calloc(Nrows*Ncols, sizeof(double));

	for(n=1;n<Nrows;++n){
		A[n] = A[n-1]+ Ncols;
	}
	return A;
}*/
/*

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

double BC(int x, int y, int problem_index){

if (problem_index == 1)
	return x;

else if (problem_index == 2 || problem_index == 3 || problem_index == 4)
	return 0;

else if (problem_index == 5)
	return 70;

}

double output(){
	
}


double **Build_LHS(float cells_per_side, int problem_index){


	// Initializing data
	float h = 1.0/cells_per_side;
	int size = cells_per_side;
	int nodes_per_side = cells_per_side + 1;

	// Building matrices

	double **index = BuildMatrix(nodes_per_side,nodes_per_side);
	double x_array[size], y_array[size];

	// Loading x and y array
	int counter = 0;
	for (double i = 0; i < 1; i = i + h)
	{
		x_array[counter] = i;
		y_array[counter] = i;

		counter = counter + 1;
	}


	// Filling index 
	for (int i = 0; i < nodes_per_side; ++i)
	{
		for (int j = 0; j < nodes_per_side; ++j)
			{
				index[i][j] = (i)*nodes_per_side + j;
			}
	}

	// Initializing RHS matrix
	double **K = BuildMatrix(nodes_per_side*nodes_per_side,nodes_per_side*nodes_per_side);


	// Setting up grid
	int x, y, index_center, index_bottom, index_top, index_left, index_right, kappa_bottom, kappa_top, kappa_left, kappa_right;
	for (int i = 1; i < cells_per_side; ++i)
	{	
		for (int j = 1; j < cells_per_side; ++j)
		{

			x = x_array[i];
			y = y_array[j];
        	index_center = index[i][j];        
        	index_bottom = index[i][j-1];
        	index_top = index[i][j+1];
        	index_left = index[i-1][j];
        	index_right = index[i+1][j];

        
        //% Determine conductivities associated with five-point stencil
        
        kappa_bottom = conductivity(x,y-h/2,problem_index);
        kappa_top = conductivity(x,y+h/2,problem_index);
        kappa_left = conductivity(x-h/2,y,problem_index);
        kappa_right = conductivity(x+h/2,y,problem_index);        
        
       
        //% Determine contributions to LHS matrix
        double temp = h*h;
        K[index_center][index_center] = (kappa_bottom + kappa_top + kappa_left + kappa_right)/temp;        
        K[index_center][index_bottom] = -kappa_bottom/temp;
        K[index_center][index_top] = -kappa_top/temp;
        K[index_center][index_left] = -kappa_left/temp;
        K[index_center][index_right] = -kappa_right/temp;
        
    }
}


// Filling K matrix
int x_left, x_right, i_left, i_right;
for (int j = 0; j < nodes_per_side; ++j)
{
    x_left = x_array[1];
    x_right = x_array[nodes_per_side];
    
    y = y_array[j];
    
    //% Determine the i indices
    
    i_left = 1-1;
    i_right = nodes_per_side-1;
    
    //% Determine the position indices
    index_left = index[i_left][j];
    index_right = index[i_right][j];
    
    //% Set diagonal entries of LHS
    K[index_left][index_left] = 1;
    K[index_right][index_right] = 1;
    

}

// Filling K matrix
int j_bottom, j_top, y_top, y_bottom;
for (int i = 0; i < nodes_per_side; ++i)
{
    x = x_array[i];
    
    y_bottom = y_array[1];
    y_top = y_array[nodes_per_side];
    
//    % Determine the j indices
    
    j_bottom = 1-1;
    j_top = nodes_per_side;
    

   // % Determine the position indices
    
    index_bottom = index[i][j_bottom];
    index_top = index[i][j_top];
    
    
    K[index_bottom][index_bottom] = 1;
    K[index_top][index_top] = 1;
    
}

return K;

}


double **Build_RHS(float cells_per_side,int problem_index){


	// Initializing data
	float h = 1.0/cells_per_side;
	int size = cells_per_side;
	int nodes_per_side = cells_per_side + 1;

	// Building matrices

	double **index = BuildMatrix(nodes_per_side,nodes_per_side);
	double x_array[size], y_array[size];

	// Loading x and y array
	int counter = 0;
	for (double i = 0; i < 1; i = i + 0.1)
	{
		x_array[counter] = i;
		y_array[counter] = i;
		counter = counter + 1;
	}

	// Filling index
	for (int i = 0; i < nodes_per_side; ++i)
	{
		for (int j = 0; j < nodes_per_side; ++j)
			{
				index[i][j] = (i)*nodes_per_side + j;
			}
	}

	// Initializing LHS matrix
	double **F = BuildMatrix(nodes_per_side*nodes_per_side,nodes_per_side*nodes_per_side);

	// Filling F matrix
int x, y, index_center, index_bottom, index_top, index_left, index_right, kappa_bottom, kappa_top, kappa_left, kappa_right;
	for (int i = 1; i < cells_per_side; ++i)
	{	
		for (int j = 1; j < cells_per_side; ++j)
		{

			x = x_array[i];
			y = y_array[j];
        	index_center = index[i][j];        
        	index_bottom = index[i][j-1];
        	index_top = index[i][j+1];
        	index_left = index[i-1][j];
        	index_right = index[i+1][j];

        
        //% Determine conductivities associated with five-point stencil
        
        kappa_bottom = conductivity(x,y-h/2,problem_index);
        kappa_top = conductivity(x,y+h/2,problem_index);
        kappa_left = conductivity(x-h/2,y,problem_index);
        kappa_right = conductivity(x+h/2,y,problem_index);        
        

        F[index_center][0] = Source(x,y,problem_index);
        
    }
}


// Filling data
int x_left, x_right, i_left, i_right;
for (int j = 0; j < nodes_per_side; ++j)
{
    x_left = x_array[1];
    x_right = x_array[nodes_per_side];
    
    y = y_array[j];
    
    //% Determine the i indices
    
    i_left = 1-1;
    i_right = nodes_per_side-1;
    
    //% Determine the position indices
    index_left = index[i_left][j];
    index_right = index[i_right][j];
    
    //% Set diagonal entries of LHS
    F[index_left][0] = BC(x_left,y,problem_index);
    F[index_right][0] = BC(x_right,y,problem_index);
    
}

// Filling data

int j_bottom, j_top, y_top, y_bottom;
for (int i = 0; i < nodes_per_side; ++i)
{
    x = x_array[i];
    
    y_bottom = y_array[1];
    y_top = y_array[nodes_per_side];
    
//    % Determine the j indices
    
    j_bottom = 1-1;
    j_top = nodes_per_side;
    

   // % Determine the position indices
    
    index_bottom = index[i][j_bottom];
    index_top = index[i][j_top];
    
    F[index_bottom][0] = BC(x,y_bottom,problem_index);
    F[index_top][0] = BC(x,y_top,problem_index);
    
}

return F;

}

*/
int main(int argc, char *argv[])
{
	// Taking user input
	int cells_per_side = atoi(argv[1]);
	int problem_index = atoi(argv[2]);

	// Calculating grid for user input
	int nodes_per_side = cells_per_side + 1;
	double **K = Build_LHS(cells_per_side,problem_index);
	double **F = Build_RHS(cells_per_side,problem_index);
	double **Answer = Build_RHS(cells_per_side,problem_index);


	// Initializing lapack variables
	lapack_int n, nrhs, lda, ldb, info;
	lapack_int ipiv[nodes_per_side*nodes_per_side];
	n = nodes_per_side;
	nrhs = 1;
	lda = nodes_per_side;
	ldb = 1;

	// Calculating matrix inverse
	info = LAPACKE_dgesv(LAPACK_ROW_MAJOR,n,nrhs,*K,lda,ipiv,*Answer,ldb);

	// Creating output file
	FILE *output;
	char name[50];
	sprintf(name,"heat_solution_%s_%s",argv[1],argv[2]);

	output = fopen(name,"w");

	// Outputting data to file
	for (int i = 0; i < n; ++i)
		fprintf(output, "%f %f %f\n",*K[i],*F[i],*Answer[i]);
	return(info);

	fclose(output);
}

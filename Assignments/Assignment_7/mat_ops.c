// Michael Tzimourakas
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cblas.h>
#include <string.h>

double **BuildMatrix(int Nrows, int Ncols){

	int n;
	double **A = (double **) calloc(Nrows,sizeof(double*));
	A[0] = (double*) calloc(Nrows*Ncols, sizeof(double));

	for(n=1;n<Nrows;++n){
		A[n] = A[n-1]+ Ncols;
	}
	return A;
}


int main(int argc, char *argv[])
{

 	// Reading in files
	FILE *file1;
	FILE *file2;
	FILE *file3;

	file1 = fopen( argv[1], "r" );
	file2 = fopen( argv[2], "r" );
	file3 = fopen( argv[3], "r" );


	// Getting size of array from file
	char str1[10], str2[10], str3[10], str4[10], str5[10], str6[10];

	fscanf(file1,"%s" "%s",str1,str2);
	fscanf(file2,"%s" "%s",str3,str4);
	fscanf(file3,"%s" "%s",str5,str6);


	int rowNums1 = atoi(str1);
	int colNums1 = atoi(str2);

	int rowNums2 = atoi(str3);
	int colNums2 = atoi(str4);

	int rowNums3 = atoi(str5);
	int colNums3 = atoi(str6);

	// Creating matrix to loa data

	double **A = BuildMatrix(rowNums1,colNums1);
	double **B = BuildMatrix(rowNums2,colNums2);
	double **C = BuildMatrix(rowNums3,colNums3);

	double **tempA = BuildMatrix(rowNums1,colNums1);
	double **temptempA = BuildMatrix(rowNums1,colNums1);

	double **tempB = BuildMatrix(rowNums2,colNums2);

	double **tempC = BuildMatrix(rowNums3,colNums3);
	double **temptempC = BuildMatrix(rowNums3,colNums3);

	double **tempAB = BuildMatrix(rowNums1,colNums2);
	double **tempBC = BuildMatrix(rowNums2,colNums3);

	// Loading data from file

	for (int i = 0; i < rowNums1; ++i)
	{
		for (int j = 0; j < colNums1; ++j)
		{	
			 fscanf(file1,"%lf", (A[i] + j));
			 tempA[i][j] = A[i][j];
			 temptempA[i][j] = A[i][j];
		}
	}

	for (int i = 0; i < rowNums2; ++i)
	{
		for (int j = 0; j < colNums2; ++j)
		{	
			 fscanf(file2,"%lf", (B[i] + j));
			 tempB[i][j] = B[i][j];
		}
	}

	for (int i = 0; i < rowNums3; ++i)
	{
		for (int j = 0; j < colNums3; ++j)
		{	
			 fscanf(file3,"%lf", (C[i] + j));
			 tempC[i][j] = C[i][j];
		}
	}

	// Initializing matrix for mulitplication

	double **AB = BuildMatrix(rowNums1,colNums2);
	double **BC = BuildMatrix(rowNums2,colNums3);
	double **ABC = BuildMatrix(rowNums1,colNums3);

	// Creating temp matricies from multiplication
	int alpha = 1;
	int beta = 1;
	cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, rowNums2, colNums3, colNums2, alpha, *B, colNums2, *C, colNums3, beta, *BC, colNums3);
	cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, rowNums1, colNums2, colNums1, alpha, *A, colNums1, *B, colNums2, beta, *AB, colNums2);

		for (int i = 0; i < rowNums1; ++i){
			for (int j = 0; j < colNums2; ++j){	
				 tempAB[i][j] = AB[i][j];
			}
		}
		for (int i = 0; i < rowNums2; ++i){
			for (int j = 0; j < colNums3; ++j){	
				 tempBC[i][j] = BC[i][j];
			}
		}

	fclose( file1 );
	fclose( file2 );
	fclose( file3 );


	FILE *output1;
	FILE *output2;
	FILE *output3;
	FILE *output4;
	FILE *output5;

	// Creating output files
	char name1[50], name2[50], name3[50], name4[50], name5[50];
	sprintf(name1,"%s_mult_%s_mult_%s",argv[1],argv[2],argv[3]);
	sprintf(name2,"%s_mult_%s_plus_%s",argv[1],argv[2],argv[3]);
	sprintf(name3,"%s_plus_%s_mult_%s",argv[1],argv[2],argv[3]);
	sprintf(name4,"%s_mult_%s_minus_%s",argv[1],argv[2],argv[3]);
	sprintf(name5,"%s_minus_%s_mult_%s",argv[1],argv[2],argv[3]);

	output1 = fopen(name1,"w");
	output2 = fopen(name2,"w");
	output3 = fopen(name3,"w");
	output4 = fopen(name4,"w");
	output5 = fopen(name5,"w");


// ABC 


if (colNums1 == rowNums2 && colNums2 == rowNums3){
int alpha = 1;
int beta = 0;
cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, rowNums1, colNums3, colNums1, alpha, *A, colNums1, *BC, colNums3, beta, *ABC, colNums3);
fprintf(output1, " %d,%d\n",rowNums1,colNums1);	
for (int i = 0; i < rowNums1; ++i){
	for (int j = 0; j < colNums3; ++j){
		fprintf(output1, "%9.4lf",ABC[i][j]);
	}
}	
}
 
 else{
 	fprintf(output1,"The following operation ABC could not be performed as matrix dimensions disagree");
}

//A*B + C

if (rowNums1 == rowNums3 && colNums1 == colNums3 && colNums1 == rowNums2){
int a = 1;
int incX = 1;
int incY = 1;
cblas_daxpy(rowNums1*colNums3,a,*AB,incX,*tempC,incY);
fprintf(output2, "%d, %d\n",rowNums1,colNums1);
	for (int i = 0; i < rowNums3; ++i){
		for (int j = 0; j < colNums3; ++j){
			fprintf(output2, "%9.4lf",tempC[i][j]);
		}
	}
}
 else{
 	fprintf(output2,"The following operation AB + C could not be performed as matrix dimensions disagree");
}

//A + BC

if (rowNums1 == rowNums2 && colNums1 == colNums3 && colNums2 == rowNums3){
int a = 1;
int incX = 1;
int incY = 1;
cblas_daxpy(rowNums1*colNums1,a,*BC,incX,*tempA,incY);
fprintf(output3, "%d,%d\n",rowNums1,colNums1);	
	for (int i = 0; i < rowNums1; ++i){
		for (int j = 0; j < colNums1; ++j){
			fprintf(output3, "%9.4lf",tempA[i][j]);
		}
	}
}

else{
	fprintf(output3,"The following operation A + BC could not be performed as matrix dimensions disagree");
}


//A*B - C

if (colNums1 == rowNums2 && colNums1 == rowNums3 && rowNums1 == colNums3){
int a = -1;
int incX = 1;
int incY = 1;
cblas_daxpy(rowNums1*colNums3,a,*C,incX,*tempAB,incY);
fprintf(output4, "%d,%d\n",rowNums1,colNums1);	
	for (int i = 0; i < rowNums1; ++i){
		for (int j = 0; j < colNums3; ++j){
			fprintf(output4, "%9.4lf ",tempAB[i][j]);
		}
	}
}

else{
	fprintf(output4,"The following operation AB - C could not be performed as matrix dimensions disagree");
}


//A - BC

if (rowNums1 == rowNums2 && colNums1 == colNums3 && colNums2 == rowNums3){
int a = -1;
int incX = 1;
int incY = 1;
cblas_daxpy(rowNums1*colNums3,a,*BC,incX,*temptempA,incY);
fprintf(output5, "%d,%d\n",rowNums1,colNums1);
for (int i = 0; i < rowNums1; ++i){
	for (int j = 0; j < colNums1; ++j){
		fprintf(output5, "%9.4lf",temptempA[i][j]);
	}
}	
}

else{
	fprintf(output5,"The following operation A - BC could not be performed as matrix dimensions disagree");
}


	fclose(output1);
	fclose(output2);
	fclose(output3);
	fclose(output4);
	fclose(output5);
	
}
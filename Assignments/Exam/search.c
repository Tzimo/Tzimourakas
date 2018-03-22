/* Michael Tzimourakas
Exam 1*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

int main(int argc,char *argv[]){
	int target = atoi(argv[2]);
	char *filename = argv[1];

	// i) Reads in target number and text file
	FILE *file;
	file = fopen( argv[1], "r" );

	// ii) Opens the file and reads in the one dimensional data array
	char number[30];
	int counter = 0;
	int *temp = malloc(500*sizeof(int));
		while (fgets(number, 1000, file) != NULL){
			temp[counter]=atoi(number);
			counter++;
		}
	fclose( file );

	// Reallocates memory to array
	int *array = realloc(temp, counter*sizeof(int));

	// iii) Searches for specified target number in array

	// Grabs file name tag if name is even or odd
	int tag = argv[1][5] - '0';
	char output_name[6];
	strncpy(output_name,argv[1],6);
	strcat(output_name,".out");
	//printf(output_name);

	// Creates file to output answer
	FILE *output;
	output = fopen(output_name,"ab+");

	// Trigger is to indicate if the number was found or not. Is tripped if found.
	int trigger;


	// Binary Search
	if (tag == 2){
	unsigned int L = 0, R = counter, M;
	while (L<R){
		M = (L+R-1)/2;
		if ( atoi(argv[2]) == array[M]){
			trigger = 1;
			fprintf(output,"The position of %d in array is %d \n",target, M);
			break;
		}
		else if ( atoi(argv[2]) < array[M]){
			L = M + 1;
		}
		else{
			R = M -1;
		}
	}
}

else{
	// Linear Search
	for (int i = 0; i < counter; ++i){
		if (array[i] == target){
			fprintf(output,"The position of %d in array is %d \n",target, i);
			trigger = 1;
			break;
		}
		else{
			continue;
			}
	}
}

	// iv) Writes out result to output file
	if (trigger != 1){
		fprintf(output,"The number %d is not in the array\n",target);
	}
	fclose(output);
}
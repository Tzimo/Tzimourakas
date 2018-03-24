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
	//Array1.out
	// Grabs file name tag if name is even or odd
	int tag = argv[1][5] - '0';
	char output_name[10];
	strncpy(output_name,argv[1],7);
	strcat(output_name,"out");
	//printf("%c\n",*output_name);

	// Creates file to output answer
	FILE *out;
	out = fopen(output_name,"a+");

	// Trigger is to i ndicate if the number was found or not. Is tripped if found.
	int trigger;

	// Binary Search
	if (tag % 2 == 0){
	int L = 0, R = counter, M;
	while (L<R){
		M = (L+R-1)/2;
		if ( atoi(argv[2]) == array[M]){
			trigger = 1;
			//FILE * output;
			//output = fopen(output_name,"a+");
			fprintf(out,"The position of %d in array is %d \n",target,M);
			printf("The position of %d in array is %d \n",target,M);
			//fclose(output);
			break;
		}
		else if ( atoi(argv[2]) < array[M]){
			R = M;
		}
		else{
			L = M + 1;
		}
	}
}

else{
	// Linear Search
	for (int i = 0; i < counter; ++i){
		if (array[i] == target){
		fprintf(out,"The position of %d in array is %d \n",target,i);
		printf("The position of %d in array is %d \n",target,i);
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
		fprintf(out,"The number %d is not in the array\n",target);
		printf("The number %d is not in the array\n",target);
	}
	fclose(out);
}
# Michael Tzimourakas
# Bash Script
#!/bin/bash

a=$1
cp $1A .
cp $1B .
cp $1C .
mkdir output_files
gcc -o mat_ops mat_ops.c -lblas -lm

for letter1 in A B C;do
	for letter2 in A B C;do
		for letter3 in A B C;do
			./mat_ops $letter1 $letter2 $letter3
		done
	done
done
mv *mult* ./output_files
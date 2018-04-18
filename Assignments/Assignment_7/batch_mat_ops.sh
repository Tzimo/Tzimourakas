# Michael Tzimourakas
# Bash Script
#!/bin/bash

a=$1
mv ~./Tzimourakas/Assignments
cd $a
gcc -o mat_ops mat_ops.c -lbas -lm
for letter1 in A B C;do
	for letter2 in A B C;do
		for letter3 in A B C;do
			./mat_ops $letter1 $letter2 $letter3
		done
	done
done

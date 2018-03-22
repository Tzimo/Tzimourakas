#!/bin/bash
# Michael Tzimourakas
# Exam Bonus
a=$1
b=0
sum=0;
if [ $a -le 0 ] || [ $a -ge 10 ] ; then
	echo "Please input a number between 1 and 10"
	exit 1
else
	for i in $(seq 1 $a); do
		let "c=($i-1)"
		let b="$b+$(( 10 ** c ))"
		echo $((i*b))
		let sum=$((sum+i*i))
	done
	echo $sum > output.txt
	exit 1
fi
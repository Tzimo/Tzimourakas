# Problem 4
a=$1
sed 's/^[^;]*;/;/' $a > temp.txt
sed 's/^.//' temp.txt > grades.txt
b=$(sed -n '$=' grades.txt)
sum=$(paste -sd+ grades.txt | bc)
avg=$((sum/b))
printf "The students average is %.2f\n" $avg
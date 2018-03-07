# Problem 1
a=$1
b=$2
c=$[b-a]
while (("$a" <= "$b")); do
	echo $a
	((a=$a+1))
done
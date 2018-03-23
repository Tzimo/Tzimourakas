a=$1
for files in Array*.in; do
	for c in 17 56 68; do
		./search $files $c
	done
done
# Michael Tzimourakas
# Ross Kloetzel
a=0.5
for c in 0 10 100 1000 10000 50000 100000; do
	./solutions 1 $c $a
	./solutions 2 $c $a
done

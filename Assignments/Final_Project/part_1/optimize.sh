# Michael Tzimourakas

# User input the file you want to run
a=$1
make

# run user input
./$a A B C

# Runs gprof to profile
gprof matrixproduct_fix_1 > analysis_fix_1.txt
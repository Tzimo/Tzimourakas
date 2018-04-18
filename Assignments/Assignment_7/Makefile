heat_solve: 
	gcc -o heat_solve main.c Build_RHS.c Build_LHS.c conductivity.c Source.c BC.c output.c BuildMatrix.c -llapacke -llapack -lblas -lgfortran -lm

clean:
	rm -f heat_solve

# main.o: main.c Build_RHS.h Build_LHS.h output.h
# 	gcc -Wall -c main.c Build_RHS.c Build_LHS.c Output.c

# Build_RHS.o: Build_RHS.c Build_RHS.h Source.h BC.h
# 	gcc -Wall -c Build_RHS.c Source.c BC.c

# Build_LHS.o: Build_LHS.c Build_LHS.h conductivity.h
# 	gcc -Wall -c Build_LHS.c Conductivity.c

# Conductivity.o: conductivity.c conductivity.h
# 	gcc -Wall -c Conductivity.c

# Source.o: Source.c Source.h
# 	gcc -Wall -c Source.c

# BC.o: BC.c BC.h
# 	gcc -Wall -c BC.c

# Output.o: output.c output.h
# 	gcc -Wall -c Output.c

# clean:
# 	rm -rf *.o heat_solve

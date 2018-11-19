CPPflags = c++ -O3 -fopenmp -std=c++11 -larmadillo

main:		main.o ising.o
			${CPPflags} main.o ising.o -o main.exe

main.o:		main.cpp 
			${CPPflags} -c main.cpp

ising.o: 	ising.cpp
			${CPPflags} -c ising.cpp


test:		test.o ising.o
			${CPPflags} test.o ising.o -o test.exe

test.o:		test.cpp
			${CPPflags} -c test.cpp


sandbox:	sandbox.o
			${CPPflags} sandbox.o -o sandbox.exe

sandbox.o:	sandbox.cpp
			${CPPflags} -c sandbox.cpp

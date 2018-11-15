CPPflags = c++ -std=c++11 -larmadillo
CPPflags1 = c++ -fopenmp -std=c++11 -larmadillo

main:		main.o ising.o
			${CPPflags1} main.o ising.o -o main.exe

main.o:		main.cpp 
			${CPPflags} -c main.cpp

ising.o: 	ising.cpp
			${CPPflags} -c ising.cpp



sandbox:	sandbox.o
			${CPPflags} sandbox.o -o sandbox.exe

sandbox.o:	sandbox.cpp
			${CPPflags} -c sandbox.cpp

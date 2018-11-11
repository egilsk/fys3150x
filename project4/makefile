CPPflags = c++ -std=c++11 -larmadillo

main:		main.o ising.o
			${CPPflags} main.o ising.o -o main.exe

main.o:		main.cpp 
			${CPPflags} -c main.cpp

ising.o: 	ising.cpp
			${CPPflags} -c ising.cpp

CPPflags = c++ -std=c++11

main:		main.o verlet.o
				${CPPflags} main.o verlet.o -o main.exe

main.o :	main.cpp 
		        	${CPPflags} -c main.cpp

verlet.o :		verlet.cpp 
				${CPPflags} -c verlet.cpp

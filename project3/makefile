CPPflags = c++ -std=c++11

main:		main.o verlet.o euler.o
				${CPPflags} main.o verlet.o euler.o -o main.exe

main.o:		main.cpp 
		        	${CPPflags} -c main.cpp

verlet.o:	verlet.cpp 
				${CPPflags} -c verlet.cpp

euler.o:	euler.cpp
				${CPPflags} -c euler.cpp

vec3.o :	vec3.cpp
				${CPPflags} -c vec3.cpp







sandbox:	sandbox.o vec3.o
				${CPPflags} sandbox.o vec3.o -o sandbox.exe

sandbox.o:	sandbox.cpp
				${CPPflags} -c sandbox.cpp

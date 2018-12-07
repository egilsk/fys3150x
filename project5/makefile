CPPflags = c++ -std=c++11

main:			main.o vec3.o atom.o system.o lennard_jones.o velocity_verlet.o statistics_sampler.o
				${CPPflags} main.o vec3.o atom.o system.o  lennard_jones.o velocity_verlet.o statistics_sampler.o -o main.exe

main.o:			main.cpp 
		        	${CPPflags} -c main.cpp

vec3.o :		vec3.cpp
				${CPPflags} -c vec3.cpp

atom.o :		 atom.cpp
				${CPPflags} -c atom.cpp

system.o :		system.cpp	
				${CPPflags} -c system.cpp

lennard_jones.o :	lennard_jones.cpp
				${CPPflags} -c lennard_jones.cpp

velocity_verlet.o:	velocity_verlet.cpp
				${CPPflags} -c velocity_verlet.cpp

statistics_sampler.o:	statistics_sampler.cpp
				${CPPflags} -c statistics_sampler.cpp



sandbox:		sandbox.o vec3.o
				${CPPflags} sandbox.o vec3.o -o sandbox.exe

sandbox.o:		sandbox.cpp
				${CPPflags} -c sandbox.cpp

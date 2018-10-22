CPPflags = c++ -std=c++11

main:		main.o vec3.o celestialbody.o system.o gravity.o forward_euler.o velocity_verlet.o
				${CPPflags} main.o vec3.o celestialbody.o system.o gravity.o forward_euler.o velocity_verlet.o -o main.exe

main.o:		main.cpp 
		        	${CPPflags} -c main.cpp

vec3.o :	vec3.cpp
				${CPPflags} -c vec3.cpp

celestialbody.o :	 celestialbody.cpp
					${CPPflags} -c celestialbody.cpp

system.o :	system.cpp
				${CPPflags} -c system.cpp

gravity.o :	gravity.cpp
				${CPPflags} -c gravity.cpp

forward_euler.o:	forward_euler.cpp
					${CPPflags} -c forward_euler.cpp

velocity_verlet.o:	velocity_verlet.cpp
				${CPPflags} -c velocity_verlet.cpp



sandbox:	sandbox.o vec3.o
				${CPPflags} sandbox.o vec3.o -o sandbox.exe

sandbox.o:	sandbox.cpp
				${CPPflags} -c sandbox.cpp

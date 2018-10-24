CPPflags = c++ -std=c++11

solar_system:		solar_system.o vec3.o celestialbody.o system.o gravity.o forward_euler.o velocity_verlet.o
			${CPPflags} solar_system.o vec3.o celestialbody.o system.o  gravity.o forward_euler.o velocity_verlet.o -o main.exe

mercury:	mercury_precession.o vec3.o celestialbody.o system.o gravity.o velocity_verlet.o
			${CPPflags} mercury_precession.o vec3.o celestialbody.o system.o gravity.o velocity_verlet.o -o mercury_precession.exe

solar_system.o:		solar_system.cpp 
		        	${CPPflags} -c solar_system.cpp

mercury_precession.o: 	mercury_precession.cpp
				${CPPflags} -c mercury_precession.cpp


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

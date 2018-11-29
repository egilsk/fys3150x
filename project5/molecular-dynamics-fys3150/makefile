CPPflags = c++ -std=c++11

main:			main.o lennardjones.o velocityverlet.o system.o statisticssampler.o atom.o io.o unitconverter.o vec3.o
				${CPPflags} main.o lennardjones.o velocityverlet.o system.o statisticssampler.o atom.o io.o unitconverter.o vec3.o -o main.exe

main.o:			main.cpp 
				${CPPflags} -c main.cpp

lennardjones.o:		lennardjones.cpp
				${CPPflags} -c lennardjones.cpp

velocityverlet.o:	velocityverlet.cpp
				${CPPflags} -c velocityverlet.cpp

system.o:		system.cpp
				${CPPflags} -c system.cpp

statisticssampler.o:	statisticssampler.cpp
				${CPPflags} -c statisticssampler.cpp

atom.o:			 atom.cpp
				${CPPflags} -c atom.cpp

io.o:			 io.cpp
				${CPPflags} -c io.cpp

unitconverter.o:	 unitconverter.cpp
				${CPPflags} -c unitconverter.cpp

vec3.o:			math/vec3.cpp
				${CPPflags} -c math/vec3.cpp

CPPflags = c++ -std=c++11

LIB = -larmadillo


test :	  		test-main.o test.o
				${CPPflags} test-main.o test.o ${LIB} -o test.exe

test-main.o :		test-main.cpp 
		        	${CPPflags} -c test-main.cpp

test.o :		test.cpp 
				${CPPflags} -c test.cpp

program:		project2_b.o jacobi.o
				${CPPflags} project2_b.o jacobi.o ${LIB} -o project2_b.exe

project2_b.o :		project2_b.cpp 
		        	${CPPflags} -c project2_b.cpp

jacobi.o :		jacobi.cpp 
				${CPPflags} -c jacobi.cpp


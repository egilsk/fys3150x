#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>
#include <armadillo>
#include <cstdlib>
#include "time.h"

using namespace std;
using namespace arma;
// Creating object for the output file
ofstream ofile;
// Defining functions
inline double f(double x) {return 100.0*exp(-10.0*x);}
inline double exact(double x) {return 1.0-(1-exp(-10))*x-exp(-10*x);}


// Begin main program
int main(int argc, char *argv[]){
  int exponent;
    // We read the highest power of 10
    if( argc <= 1 ){
      cout << "Bad Usage: " << argv[0] <<
	" reads max power 10^n" << endl;
      exit(1);
    }
    else{
      exponent = atoi(argv[1]);
    }
    // Loop over powers of 10
    for (int i = 1; i <= exponent; i++){
      // Declare new file name
      string fileout = "data";
      // Convert the power 10^i to a string
      string argument = to_string(i);
      // Final filename as filename-i-
      fileout.append(argument);
      fileout.append(".dat");
      // Initialize the number og steps n and the step size h
      int  n = (int) pow(10.0,i);
      double h = 1.0/(n+1);
      double hh = h*h;

      // GENERAL CASE

      // Set up arrays for the general case
      vec a(n);  vec b(n);  vec c(n);  vec b_tilde(n);  vec x(n+2);  vec v(n+2);
      // Quick setup of updated diagonal elements and enpoint values of x and b
      v(0) = 0; v(n+1) = 0;
      for (int i = 0; i <= n+1; i++) x(i) = i*h; 
      for (int i = 0; i < n; i++){ 
	a(i) = -1.0;
	b(i) = 2.0;
	c(i) = -1.0;
	b_tilde(i) = hh*f(x(i+1));
      }

      // Running and timing the general algorithm
      clock_t start, finish;
      start = clock();
      // Forward substitution
      for (int i = 1; i < n; i++){
        double a_b = a(i-1)/b(i-1);
	b(i) -= a_b*c(i-1);
	b_tilde(i) -= a_b*b_tilde(i-1);
      }
      // Backward substitution
	v(n) = b_tilde(n-1)/b(n-1);
	for (int i = n-1; i > 0; i--){
	  v(i) = (b_tilde(i-1) - c(i-1)*v(i+1))/b(i-1);
      }
      finish = clock();
      double time_general = (double) (finish - start)/(CLOCKS_PER_SEC);
      
      // SPECIAL CASE

      // Set up arrays for the special case
      vec b_tilde_special(n); vec v_special(n+2);
      // Setup of b-tilde and the endpoints of the solution vector
      v_special(0) = 0; v_special(n+1) = 0;
      for (int i = 0; i < n; i++){
	b_tilde_special(i) = hh*f(x(i+1));
      }

      // Running and timing the special algorithm
      start = clock();
      // Forward substitution
      for (int i = 1; i < n; i++) {
	b_tilde_special(i) += i*b_tilde_special(i-1)/(i+1);
      }			  
      // Backward substitution
      v_special(n) = n*b_tilde_special(n-1)/(n+1);
      for (int i = n-1; i > 0; i--){
	v_special(i) = i*(b_tilde_special(i-1) + v_special(i+1))/(i+1);
      }
      finish = clock();
      double time_special = (double) (finish - start)/(CLOCKS_PER_SEC);

      // LU-DECOMPOSITION
      /*
      // Initalize matrix and arrays
      mat A = zeros<mat>(n,n);  vec b_tilde_lu(n);
      // Set up matrix and arrays
      A(n-1,n-1) = 2.0; 
      for (int i = 0; i < n-1; i++){
	b_tilde_lu(i) = hh*f(x(i+1));
        A(i+1,i)  = -1.0;
        A(i,i)    = 2.0;
        A(i,i+1)  = -1.0;
      }
      // Solve Ax = b
      vec v_lu = solve(A,b_tilde_lu);
      */
      mat A = zeros<mat>(n,n);
      // Set up arrays for the simple case
      vec b_lu(n);  vec x_lu(n);
      A(0,0) = 2.0;  A(0,1) = -1;  x_lu(0) = h;  b_lu(0) =  hh*f(x_lu(0)); 
      x_lu(n-1) = x_lu(0)+(n-1)*h; b_lu(n-1) = hh*f(x_lu(n-1)); 
      for (int i = 1; i < n-1; i++){ 
        x_lu(i) = x_lu(i-1)+h; 
	b_lu(i) = hh*f(x_lu(i));
        A(i,i-1)  = -1.0;
        A(i,i)    = 2.0;
        A(i,i+1)  = -1.0;
      }
      A(n-1,n-1) = 2.0; A(n-2,n-1) = -1.0; A(n-1,n-2) = -1.0;
      // solve Ax = b
      vec solution = solve(A,b_lu);

      // Now open file and write out results
      ofile.open(fileout);
      ofile << setiosflags(ios::showpoint | ios::uppercase);
      ofile << "       x:          approx:          exact:          "<< endl;
      for (int i = 0; i <= n+1 ;i++) {
	double epsilon = log10(fabs((v(i) - exact(x(i)))/exact(x(i))));
	ofile << setw(15) << setprecision(8) << x(i);
        //ofile << setw(15) << setprecision(8) << v_lu(i);
	ofile << setw(15) << setprecision(8) << exact(x(i));
	ofile << setw(15) << setprecision(8) << epsilon << endl;
      }
      ofile << "log10 of Step size:" << endl;
      ofile << setw(15) << setprecision(8) << log10(h) << endl;
      ofile.close();
      // Printing the timing-results
      printf("Time used by general algorithm: %.4e\n", time_general);
      printf("Time used by special algorithm: %.4e\n", time_special);

    }
    return 0;
}

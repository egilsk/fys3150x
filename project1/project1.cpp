#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>
#include <armadillo>
#include <cstdlib>

// use namespace for output and input
using namespace std;
using namespace arma;
// object for output files
ofstream ofile;
// Functions used
inline double f(double x) {return 100.0*exp(-10.0*x);}
inline double exact(double x) {return 1.0-(1-exp(-10))*x-exp(-10*x);}


// Begin main program
int main(int argc, char *argv[]){
  int exponent; 
    string filename;
    // We read also the basic name for the output file and the highest power of 10^n we want
    if( argc <= 1 ){
          cout << "Bad Usage: " << argv[0] <<
              " read also file name on same line and max power 10^n" << endl;
          exit(1);
    }
        else{
        filename = argv[1]; // first command line argument after name of program
        exponent = atoi(argv[2]);
    }
    // Loop over powers of 10
    for (int i = 1; i <= exponent; i++){
      int  n = (int) pow(10.0,i);
      // Declare new file name
      string fileout = filename;
      // Convert the power 10^i to a string
      string argument = to_string(i);
      // Final filename as filename-i-
      fileout.append(argument);
      fileout.append(".dat");
      double h = 1.0/(n+1);
      double hh = h*h;
      // Set up arrays for the simple case
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
      // Now open file and write out results
      ofile.open(fileout);
      ofile << setiosflags(ios::showpoint | ios::uppercase);
      ofile << "       x:          approx:          exact:          "<< endl;
      for (int i = 0; i <= n+1 ;i++) {
	ofile << setw(15) << setprecision(8) << x(i);
        ofile << setw(15) << setprecision(8) << v(i);
	ofile << setw(15) << setprecision(8) << exact(x(i)) << endl;
      }
      ofile.close();
    }
    return 0;
}

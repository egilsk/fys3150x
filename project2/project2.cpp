#include <cmath>
#include <armadillo>

using namespace arma;

int main(int argc, char *argv[]){
  
  // Define the number of steps
  int N = 1000;
  // Define the step size
  double h = 1.0/N;
  double hh = h*h;
  
  // Define the matrix
  mat A = zeros<mat>(N-1,N-1);
  // Set up the matrix elements
  double d = 2.0/hh; double a = -1.0/hh; 
  A(N-2,N-2) = d;
  for (int i = 0; i <= N-3; i++){
    A(i,i+1) = a;
    A(i,i) = d;
    A(i+1,i) = a;
  }
  
  // Find eigenvalues with armadillo
  vec eigval_arma;
  eig_sym(eigval_arma, A);
  x
  // Define pi
  double pi = 4*atan(1);

  // Calculate the analytic eigenvalues
  vec eigval_analytic(N-1);
  for (int i = 0; i <= N-2; i++) eigval_analytic(i) = d + 2*a*cos((i+1)*pi/(N+1));

  // Print
  //printf("Armadillo:   Analytic:\n");
  for (int i = 0; i <= N-2; i++){
    double epsilon = fabs((eigval_arma(i) - eigval_analytic(i))/eigval_analytic(i));
    //printf("%10.4f   %9.4f\n", eigval_arma(i), eigval_analytic(i));
    printf("%10.5f\n", epsilon);
  }
  return 0;
}

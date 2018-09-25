#include "jacobi.h"

int main(int argc, char *argv[]){

  // Define the number of steps
  int N = 10;
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

  // Define a vector for the analytical eigenvalues
  vec eigenvalues_analytic(N-1);
  // Define pi
  double pi = 4*atan(1);
  // Calculate the analytical eigenvalues
  for (int i = 0; i <= N-2; i++){ eigenvalues_analytic(i) = d + 2*a*cos((i+1)*pi/N);}

  // Diagonalise the matrix using Jacobi
  A = Jacobi(A, 1e-8, 1000);

  // Finding eigenvalues using Armadillo
  vec eigenvalues_arma(N-1);
  eig_sym(eigenvalues_arma, A);
  
  // Define a vector for the numerical eigenvalues
  vec eigenvalues(N-1);
  // Collect the eigenvalues from the diagonal
  for (int i = 0; i <= N-2; i++){
    eigenvalues(i) = A(i,i);
  }
  // Sort the eigenvalues
  eigenvalues = sort(eigenvalues);

  // Print the numerical and analytical eigenvalues
  printf("Analytical    Armadillo    Numerical\n");
  for (int i = 0; i <= N-2; i++){
    printf("%10.5f   %10.5f   %10.5f\n", eigenvalues_analytic(i), eigenvalues_arma(i), eigenvalues(i));
  }

  return 0;
}

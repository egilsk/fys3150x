#include "jacobi.h"

int main(int argc, char *argv[]){
  // Declare the number of steps, the maximum number of iterations and the tolerance for the non-diagonal elements  
  int N; int max_iterations; double epsilon;
    // Read the number of steps, the number of iterations and the tolerance from the command line
    if( argc <= 3 ){
      cout << "Error: " << argv[0] << " reads the number of steps, the maximal number of iterations and a tolerance" << endl;
      exit(1);
    }
    else{
      N = atoi(argv[1]);
      max_iterations = atoi(argv[2]);
      epsilon = atof(argv[3]);
    }

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

  // Finding eigenvalues using Armadillo
  vec eigenvalues_arma(N-1);
  eig_sym(eigenvalues_arma, A);


  // Diagonalise the matrix using Jacobi
  A = Jacobi(A, epsilon, max_iterations);
  
  // Define a vector for the numerical eigenvalues
  vec eigenvalues(N-1);
  // Collect the eigenvalues from the diagonal matrix
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

#include "jacobi.h"

int main(int argc, char *argv[]){
  // Declare the number of steps, the maximal value of rho, the "frequency" omega_r and the maximum number of iterations  
  int N; double rho_max; double omega_r; int max_iterations;
    // Read the number of steps, rho max, omega_r and the number of iterations from the command line
    if( argc <= 4 ){
      cout << "Error: " << argv[0] << " reads the number of steps, rho_max, omega_r and the maximal number of iterations" << endl;
      exit(1);
    }
    else{
      N = atoi(argv[1]);
      rho_max = atof(argv[2]);
      omega_r = atof(argv[3]);
      max_iterations = atoi(argv[4]);
    }

  // Define the step size
  double h = (double) rho_max/N;
  double hh = h*h;
  
  // Define rho
  vec rho(N+1);
  for (int i = 0; i < N+1 ; i++){ rho(i) = i*h; }

  // Define the matrix
  mat A = zeros<mat>(N-1,N-1);
  // Set up the matrix elements
  double d = 2.0/hh; double a = -1.0/hh; double omega = omega_r*omega_r;
  A(N-2,N-2) = d + omega*rho(N-1)*rho(N-1) + 1.0/rho(N-1);
  for (int i = 0; i <= N-3; i++){
    A(i,i+1) = a;
    A(i,i) = d + omega*rho(i+1)*rho(i+1) + 1.0/rho(i+1);
    A(i+1,i) = a;
  }

  // Finding eigenvalues using Armadillo
  vec eigenvalues_arma(N-1);
  eig_sym(eigenvalues_arma, A);
  /*
  // Diagonalise the matrix using Jacobi
  A = Jacobi(A, 1e-8, max_iterations);
  
  // Define a vector for the numerical eigenvalues
  vec eigenvalues(N-1);
  // Collect the eigenvalues from the diagonal matrix
  for (int i = 0; i <= N-2; i++){
    eigenvalues(i) = A(i,i);
  }
  // Sort the eigenvalues
  eigenvalues = sort(eigenvalues);
  */
  // Compare our results with Armadillo
  printf("Armadillo    Numerical\n");
  for (int i = 0; i <= 4; i++){
    printf("%10.4f\n", eigenvalues_arma(i));
  }

  return 0;
}
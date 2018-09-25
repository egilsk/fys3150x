#include <iostream>
#include <cmath>
#include <armadillo>
#include <tuple>

using namespace std;
using namespace arma;

tuple <double,int,int> Find_max_nondiagonal(mat);
mat Jacobi(mat, double, int);

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

tuple <double,int,int> Find_max_nondiagonal(mat A){
  // Declare the maximal non-diagonal element, and its indices k and l
  double max; int k, l;
  // Define the dimension of the matrix
  int N = A.n_cols;
  // Find the largest non-diagonal element
  for (int i = 0; i < N; i++){
    for (int j = i+1; j < N; j++){
      double a_ij = fabs(A(i,j));
      if (a_ij > max){
	max = a_ij; k = i; l = j;
      }
    }
  }
return make_tuple(max, k, l);
}

mat Jacobi(mat A, double epsilon, int max_iterations){
  // Collect the maximal non-diagonal element and its indices from Find_max_nondiagonal()
  double max_nondiagonal = get<0>(Find_max_nondiagonal(A));
  int k = get<1>(Find_max_nondiagonal(A));
  int l = get<2>(Find_max_nondiagonal(A)); 
  
  // Perform the Jacobi rotation until the maximal non-diagonal element reaches the desired tolerance, or after a maximum number of iterations
  int iterations = 0;  
  while (max_nondiagonal > epsilon && iterations < max_iterations){
    // Declare tau, tan, sin and cos
    double tau,t,s,c;

    // Prevent divison by zero
    if (A(k,l) == 0){
      s = 0.0; c = 1.0;
    }
    else{
      // Calculate tau
      tau = (A(l,l) - A(k,k))/(2*A(k,l));
      // Find the smallest solution for t
      if (tau > 0){
	t = 1.0/(tau + sqrt(1.0 + tau*tau));
      }
      else{
	t = -1.0/(- tau + sqrt(1.0 + tau*tau));
      }
      // Calculate c and s
      c = 1.0/sqrt(1.0 + t*t); s = c*t;
    }

    // Perform the similarity transformation
    double a_kk = A(k,k); double a_ll = A(l,l);
    A(k,k) = c*c*a_kk - 2*c*s*A(k,l) + s*s*a_ll;
    A(l,l) = c*c*a_ll + 2*c*s*A(k,l) + s*s*a_kk;
    A(k,l) = 0.0; A(l,k) = 0.0;
    for (int i = 0; i < A.n_cols; i++){
      if (i != k && i != l){
	double a_ik = A(i,k); double a_il = A(i,l);
	A(i,k) = c*a_ik - s*a_il;
	A(i,l) = c*a_il + s*a_ik;
	A(k,i) = A(i,k);
	A(l,i) = A(i,l);
      }
}

    // Update the maximal non-diagonal element and its indices
    max_nondiagonal = get<0>(Find_max_nondiagonal(A));
    k = get<1>(Find_max_nondiagonal(A));
    l = get<2>(Find_max_nondiagonal(A));

    iterations++;
    cout << iterations << endl;

  }
  return A;
}

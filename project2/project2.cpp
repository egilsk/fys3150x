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

  mat B = Jacobi(A, 1e-10, 10);
  cout << B << endl;

  return 0;
}

tuple <double,int,int> Find_max_nondiagonal(mat A){
  // Define the maximal non-diagonal element, and its indices k and l
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
  
  double max_nondiagonal = get<0>(Find_max_nondiagonal(A));
  int k = get<1>(Find_max_nondiagonal(A));
  int l = get<2>(Find_max_nondiagonal(A)); 
  
  int iterations = 0;  
  while (max_nondiagonal > epsilon && iterations < max_iterations){
    double s,c;
    if (A(k,l) == 0){
      s = 0; c = 1;
    }
    else{
      double a_ll = A(l,l); double a_kk = A(k,k); double a_kl = A(k,l);
      double tau = (a_ll - a_kk)/(2*a_kl);
      double t = - tau + sqrt(1 + tau*tau);
      c = 1/sqrt(1 + t*t);
      s = c*t;
    }
    iterations++;
  } 
  return A;
}

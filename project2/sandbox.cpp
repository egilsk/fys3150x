#include <armadillo>
#include <iostream>
#include <tuple>
#include <typeinfo>
#include "jacobi.h"

using namespace std;
using namespace arma;

int main(int argc, char *argv[]){
  int n = 3;
  vec a  = linspace<vec>(1,n,n);
  mat A = toeplitz(a);
  
  vec eigval_before;
  vec eigval_after;
  mat eigvec_before;
  mat eigvec_after;

  eig_sym(eigval_before, eigvec_before, A);

  mat B = Jacobi(A, 1e-8, 1000);

  eig_sym(eigval_after, eigvec_after, A);

  double dot1_before = eigvec_before(0,0)*eigvec_before(0,1) + eigvec_before(1,0)*eigvec_before(1,1) +  eigvec_before(2,0)*eigvec_before(2,1); 
  double dot2_before = eigvec_before(0,0)*eigvec_before(0,2) + eigvec_before(1,0)*eigvec_before(1,2) +  eigvec_before(2,0)*eigvec_before(2,2);
  double dot3_before = eigvec_before(0,1)*eigvec_before(0,2) + eigvec_before(1,1)*eigvec_before(1,2) +  eigvec_before(2,1)*eigvec_before(2,2);
  double dot1_after = eigvec_after(0,0)*eigvec_after(0,1) + eigvec_after(1,0)*eigvec_after(1,1) +  eigvec_after(2,0)*eigvec_after(2,1); 
  double dot2_after = eigvec_after(0,0)*eigvec_after(0,2) + eigvec_after(1,0)*eigvec_after(1,2) +  eigvec_after(2,0)*eigvec_after(2,2);
  double dot3_after = eigvec_after(0,1)*eigvec_after(0,2) + eigvec_after(1,1)*eigvec_after(1,2) +  eigvec_after(2,1)*eigvec_after(2,2);  
  
  cout << dot1_before << endl;
  cout << dot2_before << endl;
  cout << dot3_before << endl;
  cout << dot1_after << endl;
  cout << dot2_after << endl;
  cout << dot3_after << endl;

  return 0;
}

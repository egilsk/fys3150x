#include <iostream>
#include <cmath>
#include <armadillo>

using namespace std;
using namespace arma;

int main(int argc, char* argv[])
{

  double Z = exp(8) + exp(-8) + 6;
  double E = 8*(exp(-8) - exp(8))/Z;
  double M = 4*(exp(8) + 2)/Z;
  double C_V = 128*(2 + 3*exp(8) + 3*exp(-8))/(Z*Z);
  double khi = 16*(3 + 3*exp(8) + exp(-8))/(Z*Z);

  cout << E << " " << M << " " << C_V << " " << khi << endl;
  
  vec A = zeros<mat>(5);
  cout << A[-1] << endl;

  return 0;
}

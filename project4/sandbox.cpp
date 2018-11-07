#include <iostream>
#include <cmath>

using namespace std;

int main(int argc, char* argv[])
{

  double Z = exp(8) + exp(-8) + 6;
  double E = 8*(exp(-8) - exp(8))/Z;
  double M = 4*(exp(8) + 2)/Z;
  double C_V = 128*(2 + 3*exp(8) + 3*exp(-8))/(Z*Z);
  double khi = 16*(exp(8) + 1)/Z;

  cout << E/4 << endl;
  cout << M/4 << endl;
  cout << C_V/4 << endl;
  cout << khi/4 << endl;
  
  return 0;
}

#include <iostream>
#include <cmath>

using namespace std;

int main(int argc, char* argv[])
{

  double Z = exp(8) + exp(-8) + 6;
  double E = 8*(exp(-8) - exp(8))/Z;
  double M = 4*(exp(8) + 2)/Z;
  double C_V = 128*(2 + 3*exp(8) + 3*exp(-8))/(Z*Z);
  double khi = 16*(3 + 3*exp(8) + exp(-8))/(Z*Z);

  cout << E << " " << M << " " << C_V << " " << khi << endl;
  
  return 0;
}

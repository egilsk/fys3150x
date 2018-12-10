#include "vec3.h"
#include <iostream>

int main (int argc, char* argv[]){

  double r = 3.0;

  cout << 1.0/r*(2.0/pow(r,12) - 1.0/pow(r,6)) << endl;

  return 0;
}

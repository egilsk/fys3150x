#include <cstdlib>
#include <iostream>
#include <cmath>
#include "vec3.h"

using namespace std;

int main (int argc, char* argv[]){

  vec3 x(1.0, 2.0, 3.0);
  vec3 y(2, 3, 4);

  x.print();
  y.print();
 
  return 0;
}

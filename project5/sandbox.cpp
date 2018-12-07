#include "vec3.h"
#include <iostream>

int main (int argc, char* argv[]){

  vec3 r(1,0,0);
  r[1] = 2;

  cout << r << endl;

  return 0;
}

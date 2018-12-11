#include "vec3.h"
#include <iostream>
#include <random>

using namespace std;

int main (int argc, char* argv[]){

  double std_dev = 1.0;
  int seed = 1997;

  // Call the Mersenne Twister generator
  mt19937_64 gen(seed);
  // Set up the uniform distribution
  normal_distribution<double> distribution(0.0, std_dev);

  for ( int i = 0; i < 10; i++) {
  
  cout << distribution(gen) << endl;
  
  }	

  return 0;
}

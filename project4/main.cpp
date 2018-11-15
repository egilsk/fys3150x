#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <string>

#include "ising.h"

using namespace  std;
using namespace arma;

// Declare output file
ofstream ofile;

int main(int argc, char* argv[])
{
  // Declare parameters read from the command line
  int n_spin, n_cycles, n_equilibration;
  double T_start, T_end, T_step;
  
  // Read from the command line
  if (argc <= 5) {
    cout << "Error: " << argv[0] << 
      " reads # of spins, # of MC cycles, # of equilibration cycles, initial and final temperature and temperature step" << endl;
    exit(1);
  }
  else{
    n_spin = atoi(argv[1]);
    n_cycles = atoi(argv[2]);
    n_equilibration = atoi(argv[3]);
    T_start = atof(argv[4]);
    T_end = atof(argv[5]);
    T_step = atof(argv[6]);
  }
  
  // Open output file
  ofile.open("ising.dat");
  // Create header
  //Header(ofile, n_cycles, n_equilibration);

  // Declare a vector which stores the expectation values
  vec values;
  
  // Loop over temperatures
  for (double T = T_start; T <= T_end; T += T_step){
    
    // Initialise expectation values
    values = zeros<mat>(5);
    
    // Run Monte Carlo sampling
    Metropolis(values, T, n_spin, n_cycles, n_equilibration, ofile);
  
    // Write to file
    //Output(ofile, values, T);
    
  }
  
  ofile.close();

  // Analytical results for 2x2 lattice

  double Z = exp(8) + exp(-8) + 6;
  double E = 8*(exp(-8) - exp(8))/Z;
  double M = 4*(exp(8) + 2)/Z;
  double C_V = 128*(2 + 3*exp(8) + 3*exp(-8))/(Z*Z);
  double khi = 16*(3 + 3*exp(8) + exp(-8))/(Z*Z);

  //cout << E << " " << M << " " << C_V << " " << khi << endl;

  return 0;
}

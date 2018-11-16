#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include "omp.h"

#include "ising.h"

using namespace  std;
using namespace arma;

// Declare output file
ofstream ofile;

int main(int argc, char* argv[])
{
  // Declare parameters read from the command line
  int n_spin, n_cycles, n_equilibration, n_temp;
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
    n_temp = atoi(argv[6]);
  }
  
  // Open output file
  ofile.open("ising.dat");
  // Create header
  //Header(ofile, n_cycles, n_equilibration);

  // Create header (for equilibration analysis)
  ofile << setiosflags(ios::showpoint | ios::left);
  ofile << "Number of MC cycles: " << n_cycles - n_equilibration << endl;
  ofile << setw(16) << "Energy";
  ofile << setw(16) << "Magnetisation";
  ofile << setw(16) << "Number_of_Accepted_Moves" << endl;

  // Create header (for probability analysis)
  //ofile << setiosflags(ios::showpoint | ios::left);
  //ofile << "Number of MC cycles: " << n_cycles << endl;
  //ofile << setw(16) << "Energy" << endl;

  // Declare a matrix which stores the expectation values
  mat values = zeros<mat>(5, n_temp);

  // Declare a matrix which stores variables for equilibration analysis 
  mat equilibrium = zeros<mat>(3, n_cycles);
  
  // Declare a vector which stores the temperatures
  vec temperature = linspace(T_start, T_end, n_temp);
    
  // Time the loop
  double start = omp_get_wtime();
  
  // Loop over temperatures
#pragma omp parallel for
  for (int i = 0; i < n_temp; i++){
  
    vec tmp(5);
    
    // Run Monte Carlo sampling
    Metropolis(tmp, equilibrium, temperature[i], n_spin, n_cycles, n_equilibration);  
    
    values.col(i) = tmp;
    
 }

  // Write to file
  //Output(ofile, values, temperature, n_spin);
  
  // Write to file (for equilibration analysis)
  for (int i = 1; i <= (n_cycles - n_equilibration); i++){
    ofile << setw(16) << setprecision(8) << equilibrium(1,i);
    ofile << setw(16) << setprecision(8) << equilibrium(2,i);
    ofile << setw(16) << setprecision(8) << equilibrium(0,i) << endl;
  }


  double finish = omp_get_wtime();
  double time_used = finish - start;
  cout << time_used << endl;

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

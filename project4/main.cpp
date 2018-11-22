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
  double T_start, T_end;
  
  // Read from the command line
  if (argc <= 6) {
    cout << "Error: " << argv[0] << 
      " reads # of spins, # of MC cycles, # of equilibration cycles, initial and final temperature and # of temperatures" << endl;
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
  Header_expectation(ofile, n_cycles, n_equilibration, n_temp, n_spin);
  //Header_equilibration(ofile, n_cycles, n_equilibration);
  //Header_probability(ofile, n_cycles, n_equilibration);
  
  // Declare a vector which stores the temperatures
  vec temperature = linspace(T_start, T_end, n_temp);

  // Declare a matrix which stores the expectation values
  mat values = zeros<mat>(5, n_temp);

  // Declare a matrix which stores variables for equilibration and probability analysis 
  mat analysis = zeros<mat>(4, n_cycles);
  
  // Time the loop
  double start = omp_get_wtime();
  
  // Loop over temperatures
#pragma omp parallel for
  for (int i = 0; i < n_temp; i++){
    
    vec tmp(5);
    
    // Run Monte Carlo sampling
    Metropolis(tmp, analysis, temperature[i], n_spin, n_cycles, n_equilibration);
    
    values.col(i) = tmp;
    
  }
  
  double finish = omp_get_wtime();
  double time_used = finish - start;
  cout << "Time used [s]: " << time_used << endl;
  
  // Write to file
  Output_expectation(ofile, values, temperature, n_spin);
  //Output_equilibration(ofile, analysis, n_spin, n_cycles, n_equilibration);
  //Output_probability(ofile, analysis, n_spin, n_cycles, n_equilibration);
  
  ofile.close();
  
  // Analytical results for 2x2 lattice
  
  double Z = exp(8) + exp(-8) + 6;
  double E = 8*(exp(-8) - exp(8))/(Z*4.0);
  double M = 4*(exp(8) + 2)/(Z*4.0);
  double C_V = 128*(2 + 3*exp(8) + 3*exp(-8))/(Z*Z*4.0);
  double khi = 16*(3 + 3*exp(8) + exp(-8))/(Z*Z*4.0);
  
  //cout << E << " " << M << " " << C_V << " " << khi << endl;

  return 0;
}

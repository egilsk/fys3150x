#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ising.h"

TEST_CASE( "Checking the expectation values for 2x2 lattice with T = 1, running 1 000 000 MC-cycles" ){

  // Define parameters for the test case
  int n_spin = 2;
  int n_cycles = 1000000;
  int n_equilibration = 0;
  double temperature = 1;

  // Divide by number of spins
  double norm = 1.0/(n_spin*n_spin);
  
  // Analytical results
  double Z = exp(8) + exp(-8) + 6;
  double E_analytical = 8*(exp(-8) - exp(8))/Z*norm;
  double M_analytical = 4*(exp(8) + 2)/Z*norm;
  double C_V_analytical = 128*(2 + 3*exp(8) + 3*exp(-8))/(Z*Z)*norm;
  double khi_analytical = 16*(3 + 3*exp(8) + exp(-8))/(Z*Z)*norm;

  // Declare a matrix which stores the expectation values
  vec values = zeros<mat>(5);

  // Declare a matrix which stores variables for equilibration and probability analysis 
  mat analysis = zeros<mat>(4, n_cycles);
  
  // Run Monte Carlo sampling
  Metropolis(values, analysis, temperature, n_spin, n_cycles, n_equilibration);
  
  double E_numerical = values(0)*norm;
  double M_numerical = values(4)*norm;
  double C_V_numerical = (values(1) - values(0)*values(0))/(temperature*temperature)*norm;
  double khi_numerical = (values(3) - values(4)*values(4))/temperature*norm;

  // Check the values
  CHECK( E_numerical == Approx(E_analytical).epsilon(0.001) );
  CHECK( M_numerical == Approx(M_analytical).epsilon(0.001) );
  CHECK( C_V_numerical == Approx(C_V_analytical).epsilon(0.1) );
  CHECK( khi_numerical == Approx(khi_analytical).epsilon(0.1) );
}

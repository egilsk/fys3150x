#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "lennard_jones.h"
#include "velocity_verlet.h"
#include "statistics_sampler.h"

using namespace std;

TEST_CASE( "Checking energy conservation for the Velocity Verlet method" ){

  // Define constants
  double sigma = 3.405e-10;    // [m]
  double epsilon = 1.651e-21;  // [J]
  double u = 1.66054e-27;      // [kg]
  double k_B = 1.38065e-23;    // [J/K]

  // Define parameters for the test case
  int n_steps = 1000;
  double time_final = 10*1e-12/(sigma*sqrt(u/epsilon));                     // [sigma*sqrt(u/epsilon)]
  int n_cells = 5;
  double temperature_initial = 200/(epsilon/k_B);                           // [epsilon/k_B]

  // Define the lattice constant and the atomic mass.
  // * The lattice constant is adjusted so that 
  // the density is that of liquid argon
  double b = 5.26e-10/sigma*1.09325;                                  // [sigma]
  double m = 39.948;                                                  // [u]

  // Define the step size
  double h = time_final/n_steps;

  // Calculate the constant h/(mass*2) (Verlet Method)
  double h_mass_two = h/(m*2);

  // Declare a vector storing the forces (Verlet Method)
  vector<vec3> forces_tmp;

  // Initialise the force, the solver and the statistics sampler
  LennardJones F;
  VelocityVerlet solver;
  StatisticsSampler sampler;
  
  // Initialise the system
  System S(n_cells, b);
  S.initialiseLattice(m, temperature_initial);
  S.resetMomentum();
  
  // Calculate the initial forces
  F.forces(&S);

  // Declare a variable for the initial total energy (after equilibration)
  double total_energy_initial;

  // Run the calculations
  for ( int j = 0; j <= n_steps; j++) {

    // Store current forces
    forces_tmp = solver.storeForces(&S);
    
    // Update position
    solver.updatePosition(&S, h, h_mass_two);
    S.periodicPosition();
    
    // Update forces
    S.resetForces();
    F.forces(&S);
    
    // Update velocity
    solver.updateVelocity(&S, h, h_mass_two, forces_tmp);
    
    // Sample after equilibration
    if (j == 20) {
      
      sampler.sampleKinetic_energy(S);
      sampler.samplePotential_energy(S);
      sampler.sampleTotal_energy(S);
  
      total_energy_initial = sampler.getTotal_energy();

    }
    
  }

  // Sample final energy
  sampler.sampleKinetic_energy(S);
  sampler.samplePotential_energy(S);
  sampler.sampleTotal_energy(S);

  double total_energy_final = sampler.getTotal_energy();

  // Check the energies
  CHECK( total_energy_final == Approx(total_energy_initial).margin(1.0) );
}

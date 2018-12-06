#include "vec3.h"
#include "atom.h"
#include "system.h"
#include "lennard_jones.h"
#include "velocity_verlet.h"

using namespace std;

int main (int argc, char* argv[]){

  // Declare the number of time steps, the final time, the number of unit cells and the initial temperature 
  int n_steps; double time_final; int n_cells; double temperature_initial;
  // Read the number of steps, the final time, the number of unit cells and the initial temperature
  if( argc <= 4 ){
    cout << "Error: " << argv[0] << " reads number of steps, final time (picoseconds), number of unit cells and initial temperature (kelvin) " << endl;
    exit(1);
  }
  else{
    n_steps = atoi(argv[1]);
    time_final = atof(argv[2])/0.100224;                              // []
    n_cells = atoi(argv[3]);
    temperature_initial = atof(argv[4])/119.735;                      // []
  }

  // Define the step size
  double h = time_final/n_steps;

  // Define epsilon and sigma
  double epsilon = 1.0;                                               // []
  double sigma = 3.405;                                               // [Angstrom]

  // Define the lattice constant and the atomic mass
  double b = 5.26;                                                    // [Angstrom]
  double m = 39.948;                                                  // [u]

  
  // Initialise the system
  System S;
  S.initialiseLattice(n_cells, b, m, temperature_initial);
   
  // Declare and open output file
  ofstream ofile;
  ofile.open("MD.xyz");
  
  // Write out the starting positions
  S.output(ofile, n_cells);
  
  // Initialise the force and the solver
  LennardJones F(epsilon, sigma);
  VelocityVerlet solver;

  // Calculate the initial forces
  F.forces(&S);
  S.resetForces();

  // Calculate the constant h/(mass*2)
  double h_mass_two = h/(S.bodies[0]->getMass()*2);

  // Declare a vector storing the forces
  vector<vec3> forces_tmp;

  // Run the calculations
  double t = 0;
  while (t < time_final) {
    
    // Store current forces
    forces_tmp = solver.storeForces(&S);
    
    // Update position
    solver.updatePosition(&S, h, h_mass_two);
    //S.periodic(n_cells, b);
    
    // Update forces
    //S.resetForces();
    //F.forces(&S);
    
    // Update velocity
    solver.updateVelocity(&S, h, h_mass_two, forces_tmp);
    
    // Update time
    t += h;
    
    // Write to file
    S.output(ofile, n_cells);
  }

  ofile.close();

  return 0;
}


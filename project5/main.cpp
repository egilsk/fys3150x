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
    cout << "Error: " << argv[0] << " reads number of steps, final time, number of unit cells and initial temperature" << endl;
    exit(1);
  }
  else{
    n_steps = atoi(argv[1]);
    time_final = atof(argv[2]); // []
    n_cells = atoi(argv[3]);
    temperature_initial = atof(argv[4]); // []
  }
  
  // Define the step size
  double h = time_final/n_steps; // []
  // Initialise time
  double t = 0.0; // []

  // Define the lattice constant
  double b = 5.26; // [Angstrom]
  
  // Initialise the system
  System S;
  S.initialiseLattice(n_cells, b, temperature_initial);
  
  // Declare and open output file
  ofstream ofile;
  ofile.open("MD.xyz");
  
  // Create header and write out the starting positions
  S.header(ofile, n);
  S.output(ofile, t);

  // Initialise the force and the solver
  Gravity F(four_pi2, mass_sun);
  VelocityVerlet solver;

  // Calculate the initial force
  F.newtonianForces(&S);

  // Calculate the constant h/(mass*2)
  vector<double> h_mass_two;
  for (int i = 0; i < S.bodies.size(); i++) {
    h_mass_two.push_back(h/(S.bodies[i]->getMass()*2));
  }

  // Declare a vector storing the forces
  vector<vec3> forces_temp;
  
  // Run the calculations
  t = 0;
  while (t < T) {
    
    // Store current forces
    forces_temp = solver.storeForces(&S);
    
    // Update position
    solver.updatePosition(&S, h, h_mass_two);
    
    // Update forces
    S.resetForces();
    F.newtonianForces(&S);
    
    // Update velocity
    solver.updateVelocity(&S, h, h_mass_two, forces_temp);
    
    // Update time
    t += h;
    
    // Write to file
    S.output(ofile, t);
  }
  
  ofile.close();
  
  return 0;
}


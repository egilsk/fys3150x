#include "vec3.h"
#include "atom.h"
#include "system.h"
#include "lennard_jones.h"
#include "velocity_verlet.h"
#include "statistics_sampler.h"

#include <chrono>

using namespace std;
using namespace chrono;

int main (int argc, char* argv[]){

  // Define constants

  double sigma = 3.405e-10;    // [m]
  double epsilon = 1.651e-21;  // [J]
  double u = 1.66054e-27;      // [kg]
  double k_B = 1.38065e-23;    // [J/K]

  // Declare the number of time steps, the final time, the number of unit cells, the "initial" and "final" temperature, and the number of temperatures
  int n_steps; double time_final; int n_cells; double temperature_initial; double temperature_final; int n_temperatures;
  // Read the number of time steps, the final time, the number of unit cells and the temperatures
  if( argc <= 6 ){
    cout << "Error: " << argv[0] << " reads number of time steps, final time (ps), number of unit cells, \"initial\" temperature (K), \"final\" temperature (K) and number of temperatures" << endl;
    exit(1);
  }
  else{
    n_steps = atoi(argv[1]);
    time_final = atof(argv[2])*1e-12/(sigma*sqrt(u/epsilon));          // [sigma*sqrt(u/epsilon)]
    n_cells = atoi(argv[3]);
    temperature_initial = atof(argv[4])/(epsilon/k_B);                 // [epsilon/k_B]
    temperature_final = atof(argv[5])/(epsilon/k_B);                   // [epsilon/k_B]
    n_temperatures = atoi(argv[6]);
  }

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

  // Declare and open output files
  //ofstream ofile_xyz;
  //ofile_xyz.open("positions.xyz"); 
  ofstream ofile_dat;
  //ofile_dat.open("statistics.dat");
  ofile_dat.open("diffusion.dat");
  
  // Create header
  sampler.header_diffusion(ofile_dat, n_temperatures);

  // Define the temperature step
  double dT = (temperature_final - temperature_initial)/(n_temperatures - 1);

  // Declare variables for the average temperature and the initial temperature for each step
  double T_average; 
  double T = temperature_initial;


  // Time the run
  auto start = high_resolution_clock::now();

  for ( int i = 0; i < n_temperatures; i++ ) {

    // Initialise the average temperature
    T_average = 0.0;    

    // Initialise the system
    System S(n_cells, b);
    S.initialiseLattice(m, T);
    S.resetMomentum();

    // Initialise the time
    double t = 0;
    
    // Calculate the initial forces
    F.forces(&S);
    
    // Write out the starting positions
    //S.output(ofile_xyz);
    
    // Create header and write out initial sample
    //sampler.header_statistics(ofile_dat, n_steps, T, epsilon, k_B);
    //sampler.sample(S, t);
    //sampler.output_statistics(ofile_dat, t, sigma, epsilon, u, k_B);

    // Equilibration
    for ( int j = 0; j < 30; j++) {
      
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
      
    }

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
      
      // Update time
      t += h;
      
      // Sample
      //sampler.sample(S, t);
      sampler.sampleKinetic_energy(S);
      sampler.sampleTemperature(S);
      T_average += sampler.getTemperature();
      
      // Write to file
      //S.output(ofile_xyz);
      //sampler.output_statistics(ofile_dat, t, sigma, epsilon, u, k_B);
      
    }
    
    // Calculate average temperature
    T_average /= n_steps + 1;

    // Sample
    sampler.sampleD(S, t);

    // Write to file
    sampler.output_diffusion(ofile_dat, T_average, epsilon, k_B);

    // Update initial temperature
    T += dT;

  }
  
  auto finish = high_resolution_clock::now();
  duration<double> time = finish - start;
  cout << "Time used [s]: " << time.count() << endl;
  
  //ofile_xyz.close();
  ofile_dat.close();
  
  return 0;
}

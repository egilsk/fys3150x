#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <random>
#include <armadillo>
#include <string>

using namespace  std;
using namespace arma;

// Declare output file
ofstream ofile;

// Periodic boundary condition
inline int periodic(int i, int limit, int add) { return (limit + i + add) % (limit); }

// Initialisation of the lattice
void Initialise(int, mat&, double&, double&);
// Monte Carlo sampling with the Metropolis algorithm
void Metropolis(int, int, double, vec&);
// Write to file
void Output(int, int, double, vec);

int main(int argc, char* argv[])
{
  // Declare parameters read from the command line
  int n_spin, n_cycles;
  double T_start, T_end, T_step;
  
  // Read from the command line
  if (argc <= 5) {
    cout << "Error: " << argv[0] << 
      " reads # of spins, # of MC cycles, initial and final temperature and temperature step" << endl;
    exit(1);
  }
  else{
    n_spin = atoi(argv[1]);
    n_cycles = atoi(argv[2]);    
    T_start = atof(argv[3]);
    T_end = atof(argv[4]);
    T_step = atof(argv[5]);
  }
  
  // Open output file
  ofile.open("ising.dat");
  
  // Create header
  ofile << setiosflags(ios::showpoint | ios::left);
  ofile << "Number of MC cycles: " << n_cycles << endl;
  ofile << setw(16) << "Temperature";
  ofile << setw(16) << "Energy";
  ofile << setw(16) << "Magnetisation";
  ofile << setw(16) << "Heat capacity";
  ofile << setw(16) << "Susceptibility" << endl;
  
  // Declare a vector which stores the expectation values
  vec values;
  
  // Loop over temperatures
  for (double T = T_start; T <= T_end; T += T_step){
    
    // Initialise expectation values
    values = zeros<mat>(5);
    
    // Run Monte Carlo sampling
    Metropolis(n_spin, n_cycles, T, values);
  
    // Write to file
    Output(n_spin, n_cycles, T, values);
    
  }
  
  ofile.close();

  return 0;
}

// Initialise the lattice, energy and magnetisation
void Initialise(int n_spin, mat& lattice,  double& energy, double& magnetic_moment)
{
  // Set up the initial lattice and magnetisation
  for (int x = 0; x < n_spin; x++){
    for (int y = 0; y < n_spin; y++){
      lattice(x,y) = 1.0;
      magnetic_moment += lattice(x,y);
    }
  }
  
  // Set up the initial energy
  for (int x = 0; x < n_spin; x++){
    for (int y = 0; y < n_spin; y++){
      energy -= lattice(x,y) * ( lattice(periodic(x,n_spin,1), y) + lattice(x, periodic(y,n_spin,1)) );
    }
  }
}

// Run the Monte Carlo sampling with the Metropolis algorithm
void Metropolis(int n_spin, int n_cycles, double T, vec& values)
{
  // Initialize the seed and call the Mersenne algo
  std::random_device rd;
  std::mt19937_64 gen(rd());
  // Then set up the uniform distribution for x \in [[0, 1]
  std::uniform_real_distribution<double> distribution(0.0,1.0);
  // Allocate memory for spin matrix
  mat lattice = zeros<mat>(n_spin,n_spin);
  // Initialise energy and magnetization 
  double energy = 0.0; double magnetic_moment = 0.0;
  // initialize array for expectation values
  Initialise(n_spin, lattice, energy, magnetic_moment);
  // setup array for possible energy changes
  vec EnergyDifference = zeros<mat>(17); 
  for ( int de =-8; de <= 8; de+=4) EnergyDifference(de+8) = exp(-de/T);
  for (int cycles = 1; cycles <= n_cycles; cycles++){
    // The sweep over the lattice, looping over all spin sites
    for (int x = 0; x < n_spin; x++) {
      for (int y = 0; y < n_spin; y++){
	int ix = (int) (distribution(gen)*(double)n_spin);
	int iy = (int) (distribution(gen)*(double)n_spin);
	int deltaE =  2*lattice(ix,iy)*
	  (lattice(ix,periodic(iy,n_spin,-1))+
	   lattice(periodic(ix,n_spin,-1),iy) +
	   lattice(ix,periodic(iy,n_spin,1)) +
	   lattice(periodic(ix,n_spin,1),iy));
	if ( distribution(gen) <= EnergyDifference(deltaE+8) ) {
	  lattice(ix,iy) *= -1.0;  // flip one spin and accept new spin config
	  magnetic_moment += (double) 2*lattice(ix,iy);
	  energy += (double) deltaE;
	}
      }
    }
    // update expectation values  for local node
    values(0) += energy;
    values(1) += energy*energy;
    values(2) += magnetic_moment;    
    values(3) += magnetic_moment*magnetic_moment; 
    values(4) += fabs(magnetic_moment);
  }
}

// Write the results to the output file
void Output(int n_spin, int n_cycles, double T, vec values)
{
  // Divide by number of cycles
  double norm = 1.0/((double) n_cycles); 
  
  // Find expectation values
  double E_value = values(0)*norm;
  double E2_value = values(1)*norm;
  double M_value = values(2)*norm;
  double M2_value = values(3)*norm;
  double Mabs_value = values(4)*norm;
  
  // Find variance
  double E_variance = (E2_value - E_value*E_value);
  double M_variance = (M2_value - Mabs_value*Mabs_value);
  
  // Write to file
  ofile << setw(16) << setprecision(8) << T;
  ofile << setw(16) << setprecision(8) << E_value;
  ofile << setw(16) << setprecision(8) << Mabs_value;
  ofile << setw(16) << setprecision(8) << E_variance/(T*T);
  ofile << setw(16) << setprecision(8) << M_variance/T << endl;
}

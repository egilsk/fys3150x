#include "ising.h"


// Initialise the lattice, energy and magnetisation
void Initialise(mat& lattice, double& energy, double& magnetic_moment, int n_spin)
{
  // Initialise seed and set up uniform distribution
  default_random_engine gen;
  uniform_real_distribution<double> distribution(0,1);
  
  // Set up the initial lattice
  for (int x = 0; x < n_spin; x++){
    for (int y = 0; y < n_spin; y++){
      
      // All spins up
      //lattice(x, y) = 1.0;

      // Random orientation
      if ( distribution(gen) < 0.5 ){
	lattice(x, y) = 1.0;
      }
      else{
	lattice(x, y) = -1.0;
      }
     
      // Set up initial magnetisation
      magnetic_moment += lattice(x, y);
    }
  }
  
  // Set up the initial energy
  for (int x = 0; x < n_spin; x++){
    for (int y = 0; y < n_spin; y++){
      energy -= lattice(x, y) * ( lattice(periodic(x,n_spin,1), y) + lattice(x, periodic(y,n_spin,1)) );
    }
  }
}



// Run the Monte Carlo sampling with the Metropolis algorithm
void Metropolis(vec& values, double T, int n_spin, int n_cycles, ofstream& ofile)
{

  // Create header (for equilibration considerations)
  ofile << setiosflags(ios::showpoint | ios::left);
  ofile << "Number of MC cycles: " << n_cycles << endl;
  ofile << setw(16) << "Energy";
  ofile << setw(16) << "Magnetisation";
  ofile << setw(16) << "Number_of_Accepted_Moves" << endl;
  
  // Declare a variable storing the number of accepted moves
  int accepted;

  // Initialise the seed generator
  random_device rd;
  // Call the Mersenne Twister generator
  mt19937_64 gen(rd());
  // Set up the uniform distribution
  uniform_real_distribution<double> distribution(0.0, 1.0);
  
  // Declare a matrix for the lattice
  mat lattice = zeros<mat>(n_spin, n_spin);
  // Declare variables for the energy and magnetization 
  double E = 0.0; double M = 0.0;
  
  // Initialise the lattice, energy and magnetisation
  Initialise(lattice, E, M, n_spin);

  // Set up vector for possible energy changes
  vec E_changes = zeros<mat>(5);
  for (int i = -2; i <= 2; i++) E_changes(i+2) = exp(-4*i/T);
  // Define pointer to access energy changes
  double* Energy_changes = &E_changes(2);
  
  // Monte Carlo sampling
  for (int cycles = 1; cycles <= n_cycles; cycles++){
    
    accepted = 0;
    
    // Sweep over the lattice
    for (int x = 0; x < n_spin; x++) {
      for (int y = 0; y < n_spin; y++){
	
	// Select random position
	int ix = distribution(gen)*n_spin;
	int iy = distribution(gen)*n_spin;
	
	// Calculate the change in energy (modified)
	int delta_E = 0.5*lattice(ix, iy)*
	  (lattice(ix, periodic(iy,n_spin,-1)) +
	   lattice(periodic(ix,n_spin,-1), iy) +
	   lattice(ix, periodic(iy,n_spin,1)) +
	   lattice(periodic(ix,n_spin,1), iy));
	
	// Metropolis test
	if ( distribution(gen) <= Energy_changes[delta_E] ){
	  
	  // Flip spin
	  lattice(ix, iy) *= -1.0;

	  // Update energy and magnetisation
	  E += 4.0*delta_E;
	  M += 2.0*lattice(ix, iy);

	  accepted += 1;

	}

      }
    }
    
    // Add contribution to expectation values
    values(0) += E; values(1) += E*E;
    values(2) += M; values(3) += M*M;
    values(4) += fabs(M);
    
    // Write to file (for equilibration considerations)
    ofile << setw(16) << setprecision(8) << values(0)/cycles;
    ofile << setw(16) << setprecision(8) << values(4)/cycles;
    ofile << setw(16) << setprecision(8) << accepted << endl;
    
  }
  
  // Divide by number of cycles
  double norm = 1.0/n_cycles;
  
  // Find expectation values
  values *= norm;
  
}

// Create header for the output file
void Header(ofstream& ofile, int n_cycles)
{
  ofile << setiosflags(ios::showpoint | ios::left);
  ofile << "Number of MC cycles: " << n_cycles << endl;
  ofile << setw(16) << "Temperature";
  ofile << setw(16) << "Energy";
  ofile << setw(16) << "Magnetisation";
  ofile << setw(16) << "Heat_capacity";
  ofile << setw(16) << "Susceptibility" << endl;
}


// Write the results to the output file
void Output(ofstream& ofile, vec values, double T)
{
  // Find variance
  double E_variance = (values(1) - values(0)*values(0));
  double M_variance = (values(3) - values(4)*values(4));
  
  // Write to file
  ofile << setw(16) << setprecision(8) << T;
  ofile << setw(16) << setprecision(8) << values(0);
  ofile << setw(16) << setprecision(8) << values(4);
  ofile << setw(16) << setprecision(8) << E_variance/(T*T);
  ofile << setw(16) << setprecision(8) << M_variance/T << endl;
}
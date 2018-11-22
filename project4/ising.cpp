#include "ising.h"


// Initialise the lattice, energy and magnetisation
void Initialise(mat& lattice, double& energy, double& magnetic_moment, int n_spin)
{
  // Initialise seed and set up uniform distribution
  random_device rd;
  uniform_real_distribution<double> distribution(0,1);
  
  // Set up the initial lattice
  for (int x = 0; x < n_spin; x++){
    for (int y = 0; y < n_spin; y++){
      
      // All spins up
      //lattice(x, y) = 1.0;

      // Random orientation
      if ( distribution(rd) < 0.5 ){
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
void Metropolis(vec& values, mat& analysis, double T, int n_spin, int n_cycles, int n_equilibration)
{
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
    
  // Equilibration cycles
  for (int cycles = 1; cycles <= n_equilibration; cycles++){

    // Sweep over the lattice
    for (int sweep = 0; sweep < n_spin*n_spin; sweep++) {
      
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
	
      }
      
    }
    
  }

  // Declare a counter for the number of accepted moves
  unsigned long long accepted = 0;

  // Monte Carlo sampling
  for (int cycles = 0; cycles < (n_cycles - n_equilibration); cycles++){
    
    // Sweep over the lattice
    for (int sweep = 0; sweep < n_spin*n_spin; sweep++) {
      
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
    
    // Add contribution to expectation values
    values(0) += E; values(1) += E*E;
    values(2) += M; values(3) += M*M;
    values(4) += fabs(M);
    
    analysis(0, cycles) = (double) accepted/((cycles+1)*n_spin*n_spin);
    analysis(1, cycles) = values(0)/(cycles+1);
    analysis(2, cycles) = values(4)/(cycles+1);
    analysis(3, cycles) = E;
  }
  
  // Divide by number of cycles
  double norm = 1.0/(n_cycles - n_equilibration);

  // Find expectation values
  values *= norm;
  
  }

// Create header for the output file (expectation values)
void Header_expectation(ofstream& ofile, int n_cycles, int n_equilibration, int n_temp, int n_spin)
{
  ofile << setiosflags(ios::showpoint | ios::left);
  ofile << "Number of MC cycles: " << n_cycles - n_equilibration << endl;
  ofile << "Number of Temperatures: " << n_temp << endl;
  ofile << "Number of Spins: " << n_spin << endl;
  ofile << setw(16) << "Temperature";
  ofile << setw(16) << "Energy";
  ofile << setw(16) << "Magnetisation";
  ofile << setw(16) << "Heat_capacity";
  ofile << setw(16) << "Susceptibility" << endl;
}

// Create header (for equilibration analysis)
void Header_equilibration(ofstream& ofile, int n_cycles, int n_equilibration)
{
  ofile << setiosflags(ios::showpoint | ios::left);
  ofile << "Number of MC cycles: " << n_cycles - n_equilibration << endl;
  ofile << setw(16) << "Energy";
  ofile << setw(16) << "Magnetisation";
  ofile << setw(16) << "Number_of_Accepted_Moves" << endl;
}

// Create header (for probability analysis)
void Header_probability(ofstream& ofile, int n_cycles, int n_equilibration)
{
  ofile << setiosflags(ios::showpoint | ios::left);
  ofile << "Number of MC cycles: " << n_cycles - n_equilibration << endl;
  ofile << setw(16) << "Energy" << endl;
}

// Write the results to the output file (expectation values)
void Output_expectation(ofstream& ofile, mat values, vec T, int n_spin)
{
  // Loop over temperature
  for (int i = 0; i < T.n_elem; i++){ 
    
    // Find variance
    double E_variance = (values(1,i) - values(0,i)*values(0,i));
    double M_variance = (values(3,i) - values(4,i)*values(4,i));
    
    // Divide by number of spins
    double norm = 1.0/(n_spin*n_spin);
    
    // Write to file
    ofile << setw(16) << setprecision(8) << T(i);
    ofile << setw(16) << setprecision(8) << values(0,i)*norm;
    ofile << setw(16) << setprecision(8) << values(4,i)*norm;
    ofile << setw(16) << setprecision(8) << E_variance*norm*norm; ///(T(i)*T(i))*norm;
    ofile << setw(16) << setprecision(8) << M_variance/T(i)*norm << endl;
    
  }
}

// Write to file (for equilibration analysis)
void Output_equilibration(ofstream& ofile, mat analysis, int n_spin, int n_cycles, int n_equilibration)
{
  // Loop over cycles
  for (int i = 0; i < (n_cycles - n_equilibration); i++){
    ofile << setw(16) << setprecision(8) << analysis(1,i)/(n_spin*n_spin);
    ofile << setw(16) << setprecision(8) << analysis(2,i)/(n_spin*n_spin);
    ofile << setw(16) << setprecision(8) << analysis(0,i) << endl;
  }  
}


// Write to file (for probability analysis)
void Output_probability(ofstream& ofile, mat analysis, int n_spin, int n_cycles, int n_equilibration)
{
  // Loop over cycles
  for (int i = 0; i < (n_cycles - n_equilibration); i++){
    ofile << setw(16) << setprecision(8) << analysis(3,i)/(n_spin*n_spin) << endl;
  }
  
}

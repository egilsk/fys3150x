#ifndef SYSTEM_H
#define SYSTEM_H

#include "atom.h"

#include <random>

using namespace std;

class System {

 public:

  // Constructor
  System() {};

  // Destructor
  ~System() {}

  // Vector containing the objects
  vector<Atom*> bodies;

  // Add an object to the system 
  void addObject(Atom* new_body) { bodies.push_back(new_body); }

  // Reset the forces on the objects
  void resetForces();

  // Reset the potential energy of the objects
  void resetPotential();

  // Initialise the FCC-lattice
  void initialiseLattice(int n_cells, double b, double m, double T);

  // Apply periodic boundary conditions
  void periodic(int n_cells, double b);

  // Write the position of the objects to file
  void output(ofstream& ofile, int);
  
};

#endif // SYSTEM_H

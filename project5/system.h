#ifndef SYSTEM_H
#define SYSTEM_H

#include "atom.h"

#include <random>

using namespace std;

class System {

 private:

  int m_n_cells;
  double m_b;
  int m_n_atoms;
  double m_size;

 public:

  // Constructor
  System(int n_cells, double b);

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

  // Reset the net momentum
  void resetMomentum();

  // Initialise the FCC-lattice
  void initialiseLattice(double m, double T);

  // Apply periodic boundary conditions
  void periodicPosition();
  void periodicDistance(vec3* r_ij);

  // Write the position of the objects to file
  void output(ofstream& ofile);
  
};

#endif // SYSTEM_H

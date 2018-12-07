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
  double m_potential_energy;

 public:

  // Constructors
  System() {}
  System(int n_cells, double b);

  // Destructor
  ~System() {}

  // Vector containing the objects
  vector<Atom*> bodies;

  // Add an object to the system 
  void addObject(Atom* new_body) { bodies.push_back(new_body); }

  // Reset the forces on the objects
  void resetForces();

  // Reset the net momentum
  void resetMomentum();

  // Getters and setters
  int getN_cells() { return m_n_cells; } 
  int getB() { return m_b; }
  int getN_atoms() { return m_n_atoms; }
  int getSize() { return m_size; }
  double getPotential_energy() { return m_potential_energy; }
  void setPotential_energy(double potential_energy) { m_potential_energy = potential_energy; }

  // Initialise the FCC-lattice
  void initialiseLattice(double m, double T);

  // Apply periodic boundary conditions
  void periodicPosition();
  void periodicDistance(vec3* r_ij);

  // Write the position of the objects to file
  void output(ofstream& ofile);
  
};

#endif // SYSTEM_H

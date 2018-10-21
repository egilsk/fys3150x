#ifndef SYSTEM_H
#define SYSTEM_H

#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>

#include "celestialbody.h"

using namespace std;

class System {

 public:

  // Constructor
  System() {};

  // Destructor
  ~System() {}

  // Vector containing the solar system objects
  vector<CelestialBody*> bodies;

  // Add an object to the system 
  void addObject(CelestialBody* new_body) { bodies.push_back(new_body); }

  // Reset the forces on the objects
  void resetForces();

  // Initialise and create header for an output file
  void header(ofstream& ofile, int);
  
  // Write the position of the objects to file
  void output(ofstream& ofile, double);
  
};

#endif // SYSTEM_H

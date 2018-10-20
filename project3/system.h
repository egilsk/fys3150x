#ifndef SYSTEM_H
#define SYSTEM_H

#include <vector>

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

};

#endif // SYSTEM_H

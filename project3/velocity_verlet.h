#ifndef VELOCITY_VERLET_H
#define	VELOCITY_VERLET_H

#include "system.h"

class VelocityVerlet
{
  
 public:
  
  // Constructor
  VelocityVerlet() {}
  
  // Destructor
  ~VelocityVerlet() {}
  
  // Store the current forces on the objects of the system
  vector<vec3> storeForces(System* system);

  // Update the positions of the objects in the system
  void updatePosition(System* system, const double h, const vector<double> h_mass_two);

  // Update the velocities of the objects in the system
  void updateVelocity(System* system, const double h, const vector<double> h_mass_two, vector<vec3> forces_temp);

};

#endif // VELOCITY_VERLET_H

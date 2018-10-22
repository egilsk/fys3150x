#ifndef VELOCITY_VERLET_H
#define	VELOCITY_VERLET_H

#include "system.h"
#include "gravity.h"

class VelocityVerlet
{
  
 public:
  
  // Constructor
  VelocityVerlet() {}
  
  // Destructor
  ~VelocityVerlet() {}
  
  void integrate(System* system, Gravity* gravity, const double h, const vector<double> h_mass_two);

};

#endif // VELOCITY_VERLET_H

#ifndef NEWTONIAN_GRAVITY_H
#define NEWTONIAN_GRAVITY_H

#include "system.h"

class NewtonianGravity
{
  
 private:
  
  double m_G;
  double m_solar_mass;

 public:
  
  // Constructor
  NewtonianGravity(double G, double solar_mass);  
  
  // Destructor
  ~NewtonianGravity() {}
  
  // Calculate the gravitational forces between the objects in the system
  void forces(System* system);

  // Calculate the potential energy of the objects in the system
  void potential(System* system);
  
};

#endif // NEWTONIAN_GRAVITY_H

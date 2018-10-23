#ifndef GRAVITY_H
#define GRAVITY_H

#include "system.h"

class Gravity
{
  
 private:
  
  double m_G;
  double m_solar_mass;
  double m_c;

 public:
  
  // Constructor
  Gravity(double G, double solar_mass);
  Gravity(double G, double solar_mass, double c);
  
  // Destructor
  ~Gravity() {}
  
  // Calculate the newtonian gravitational forces between the objects in the system
  void newtonianForces(System* system);

  // Calculate the classical potential energy of the objects in the system
  void potential(System* system);

  // Calculate the relativistic gravitational forces between the objects in the system
  void relativisticForces(System* system);
  
};

#endif // NEWTONIAN_GRAVITY_H

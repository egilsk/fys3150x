#ifndef GRAVITY_H
#define GRAVITY_H

#include "system.h"

class Gravity
{
  
 private:
  
  double m_G;
  double m_solar_mass;
  
 public:
  
  // Constructor
  Gravity(double G, double sunMass);
  
  // Destructor
  ~Gravity() {}
  
  // Calculate the gravitational forces between the objects in the system
  void forces(System* system);
  
  // Calculate the potential energy of the objects in the system
  void potential(System* system);
  
};

#endif // GRAVITY_H

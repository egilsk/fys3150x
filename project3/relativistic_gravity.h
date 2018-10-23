#ifndef RELATIVISTIC_GRAVITY_H
#define RELATIVISTIC_GRAVITY_H

#include "system.h"

class RelativisticGravity
{
  
 private:
  
  double m_G;
  double m_solar_mass;
  double m_c;

 public:
  
  // Constructor
  RelativisticGravity(double G, double solar_mass, double c);  
  
  // Destructor
  ~RelativisticGravity() {}
  
  // Calculate the gravitational forces between the objects in the system
  void forces(System* system);
  
};

#endif // RELATIVISTIC_GRAVITY_H

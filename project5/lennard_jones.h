#ifndef LENNARD_JONES_H
#define LENNARD_JONES_H

#include "lennard_jones.h"

class LennardJones
{
  
 private:
  
  // Physical constants
  double m_G;
  double m_solar_mass;

 public:
  
  // Constructors
  LennardJones(double G, double solar_mass);
  // Destructor
  ~LennardJones() {}
  
  // Calculate the forces between the objects in the system
  void forces(System* system);

  // Calculate the potential energy of the objects in the system
  void potential(System* system);
  
};

#endif // LENNARD_JONES_H

#ifndef LENNARD_JONES_H
#define LENNARD_JONES_H

#include "lennard_jones.h"

class LennardJones
{
  
 private:
  
  // Physical constants
  double m_epsilon;
  double m_sigma;

 public:
  
  // Constructors
  LennardJones(double epsilon, double sigma);
  // Destructor
  ~LennardJones() {}
  
  // Calculate the forces between the objects in the system
  void forces(System* system);

  // Calculate the potential energy of the objects in the system
  void potential(System* system);
  
};

#endif // LENNARD_JONES_H

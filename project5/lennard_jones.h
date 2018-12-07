#ifndef LENNARD_JONES_H
#define LENNARD_JONES_H

#include "system.h"

class LennardJones
{

 public:
  
  // Constructor
  LennardJones() {}
  // Destructor
  ~LennardJones() {}
  
  // Calculate the forces between the objects in the system, and the potential energy of the system
  void forces(System* system);

};

#endif // LENNARD_JONES_H

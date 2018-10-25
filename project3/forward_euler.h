#ifndef FORWARD_EULER_H
#define FORWARD_EULER_H

#include "system.h"

class ForwardEuler
{
  
 public:
  
  // Constructor
  ForwardEuler() {}

  // Destructor
  ~ForwardEuler() {}

  // Integrator
  void integrate(System* system, const double h);
  
};

#endif // FORWARD_EULER_H

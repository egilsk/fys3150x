#ifndef FORWARD_EULER_H
#define FORWARD_EULER_H

#include "system.h"
#include "gravity.h"

class ForwardEuler
{
  
 public:
  
  // Constructor
  ForwardEuler() {}

  // Destructor
  ~ForwardEuler() {}
  
  void integrate(System* system, Gravity* gravity, const double h);
  
};

#endif // FORWARD_EULER_H

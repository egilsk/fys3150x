#ifndef VERLET_H
#define	VERLET_H

#include "system.h"
#include "gravity.h"

class Verlet
{
  
 public:
  
  // Constructor
  Verlet() {}
  
  // Destructor
  ~Verlet() {}
  
  void integrate(System* system, Gravity* gravity, const double h);
  
};

#endif // VERLET_H

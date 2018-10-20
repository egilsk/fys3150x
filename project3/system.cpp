#include "system.h"

void System::resetForces()
{
  for (CelestialBody* object : bodies) { object->force = {0,0,0}; }
}

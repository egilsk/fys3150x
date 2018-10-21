#include "forward_euler.h"

void ForwardEuler::integrate(System* system, Gravity* gravity, const double h)
{
  vec3 velocity_temp(0,0,0);

  // Reset forces
  system->resetForces();
  // Calculate forces
  gravity->forces(system);
  
  for (CelestialBody* object : system->bodies) {
    
    velocity_temp = object->getVelocity() + object->getForce()/object->getMass()*h;

    object->setPosition(object->getPosition() +  object->getVelocity()*h);    
    
    object->setVelocity(velocity_temp);
    
  }
}

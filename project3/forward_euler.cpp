#include "forward_euler.h"

void ForwardEuler::integrate(System* system, Gravity* gravity, const double h)
{
  // Reset and update forces
  system->resetForces();
  gravity->forces(system);

  vec3 velocity_temp(0,0,0);
  
  for (CelestialBody* object : system->bodies) {
    
    velocity_temp = object->getVelocity() + object->getForce()/object->getMass()*h;

    object->setPosition(object->getPosition() +  object->getVelocity()*h);    
    
    object->setVelocity(velocity_temp);
    
  }
}

#include "forward_euler.h"

void ForwardEuler::integrate(System* system, const double h)
{
  // Initialise vec3 storing the new velocity
  vec3 velocity_temp(0,0,0);
  
  // Perform the integration
  for (CelestialBody* object : system->bodies) {
    
    velocity_temp = object->getVelocity() + object->getForce()/object->getMass()*h;

    object->setPosition(object->getPosition() +  object->getVelocity()*h);    
    
    object->setVelocity(velocity_temp);
    
  }
}

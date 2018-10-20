#include "forward_euler.h"

void ForwardEuler::integrate(System* system, const double h)
{
  vec3 velocity_temp(0,0,0);

  for (CelestialBody* object : system->bodies) {
    
    velocity_temp = object->getVelocity() + object->force/object->getMass()*h;

    object->setPosition(object->getPosition() +  velocity_temp*h);    
    
    object->setVelocity(velocity_temp);
    
  }
}

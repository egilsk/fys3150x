#include "forward_euler.h"

void ForwardEuler::integrate(System* system, const double h)
{
  // Initialise vec3 storing the new velocity
  vec3 velocity_temp(0,0,0);
  
  // Perform the integration
  for (int i = 0; i < system->bodies.size(); i++) {
    
    velocity_temp = system->bodies[i]->getVelocity() + system->bodies[i]->getForce()/system->bodies[i]->getMass()*h;

    system->bodies[i]->setPosition(system->bodies[i]->getPosition() +  system->bodies[i]->getVelocity()*h);    
    
    system->bodies[i]->setVelocity(velocity_temp);
    
  }
}

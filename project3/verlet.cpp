#include "verlet.h"

using namespace std;

void Verlet::integrate(System* system, Gravity* gravity, const double h)
{
  vector<vec3> forces_temp;
  
  // Store old forces
  for (int i = 0; i < system->bodies.size(); i++) {
    
    forces_temp.push_back(system->bodies[i]->getForce());

  }

  // Update position
  for (CelestialBody* object : system->bodies) {   

    object->setPosition(object->getPosition() + object->getVelocity()*h + object->getForce()/object->getMass()*h*h/2);
    
  }

  // Reset forces
  system->resetForces();
  // Calculate new forces
  gravity->forces(system);

  // Update velocity
  for (int i = 0; i < system->bodies.size(); i++) {  
    
    system->bodies[i]->setVelocity( system->bodies[i]->getVelocity() + ( system->bodies[i]->getForce() + forces_temp[i] )/system->bodies[i]->getMass()*h/2 );
   
  }
}


#include "velocity_verlet.h"

using namespace std;

vector<vec3> VelocityVerlet::storeForces(System* system)
{
  // Initialise a vector storing the current forces
  vector<vec3> forces_temp;
  
  // Store the forces
  for (int i = 0; i < system->bodies.size(); i++) {
    
    forces_temp.push_back(system->bodies[i]->getForce());
    
  }

  return forces_temp;
}

void VelocityVerlet::updatePosition(System* system, const double h, const double h_mass_two)
{
  // Update the position
  for (int i = 0; i < system->bodies.size(); i++) {
    
    system->bodies[i]->setPosition( system->bodies[i]->getPosition() + system->bodies[i]->getVelocity()*h + system->bodies[i]->getForce()*h*h_mass_two );
    
  }
}

void VelocityVerlet::updateVelocity(System* system, const double h, const double h_mass_two, vector<vec3> forces_temp)
{
  // Update the velocity
  for (int i = 0; i < system->bodies.size(); i++) {  
    
    system->bodies[i]->setVelocity( system->bodies[i]->getVelocity() + ( system->bodies[i]->getForce() + forces_temp[i] )*h_mass_two );  
    
  }
  
}

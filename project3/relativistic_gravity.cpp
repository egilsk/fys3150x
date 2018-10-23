#include "relativistic_gravity.h"

RelativisticGravity::RelativisticGravity(double G, double solar_mass, double c)
{
  m_G = G;
  m_solar_mass = solar_mass;
  m_c = c;
}

void RelativisticGravity::forces(System* system)
{
  // Initialise the distance and force
  double r = 0;
  vec3 r_vec(0, 0, 0);
  vec3 force(0, 0, 0);
  
  // Calculate the forces between the objects
  for (int i = 0; i < system->bodies.size(); i++) {
    for (int j = i + 1; j < system->bodies.size(); j++) {
      
      // Calculate the distance between object i and j
      r_vec = system->bodies[i]->getPosition() - system->bodies[j]->getPosition();
      r = r_vec.length();
      
      // Calculate the force from object j on i
      force = r_vec * (-m_G) * system->bodies[i]->getMass() * system->bodies[j]->getMass() / (m_solar_mass*r*r*r) \
	* (1 + 3 * system->bodies[i]->getAngular_momentum().lengthSquared() / ( system->bodies[i]->getMass() * r*r*m_c*m_c )) ;
      
      system->bodies[i]->setForce(system->bodies[i]->getForce() + force);
      
      // Use N3L to calculate the force from object i on j
      system->bodies[j]->setForce(system->bodies[j]->getForce() - force);
      
    }
  }
}

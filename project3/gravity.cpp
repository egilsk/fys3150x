#include "gravity.h"

Gravity::Gravity(double G, double solar_mass)
{
  m_G = G;
  m_solar_mass = solar_mass;
}

Gravity::Gravity(double G, double solar_mass, double c)
{
  m_G = G;
  m_solar_mass = solar_mass;
  m_c = c;
}

void Gravity::newtonianForces(System* system)
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
      force = r_vec * (-m_G) * system->bodies[i]->getMass() * system->bodies[j]->getMass() / (m_solar_mass*r*r*r);
      system->bodies[i]->setForce(system->bodies[i]->getForce() + force);
      
      // Use N3L to calculate the force from object i on j
      system->bodies[j]->setForce(system->bodies[j]->getForce() - force);
      
    }
  }
}

void Gravity::relativisticForces(System* system)
{
  // Initialise the distance and force
  double r = 0;  vec3 r_vec(0, 0, 0);  vec3 force(0, 0, 0);
  
  // i=0 -> planet, i = 1 -> sun

  // Calculate the distance between the planet and the sun
  r_vec = system->bodies[0]->getPosition() - system->bodies[1]->getPosition();
  r = r_vec.length();

  // Calculate the angular momentum of the planet
  system->bodies[0]->setAngular_momentum();

  // Calculate the force from the sun on the planet
  force = r_vec * (-m_G) * system->bodies[0]->getMass() / (r*r*r) \
    * (1 + 3*system->bodies[0]->getAngular_momentum().lengthSquared() / (r*r*m_c*m_c )) ;
  
  system->bodies[0]->setForce(system->bodies[0]->getForce() + force);
  
  // Use N3L to calculate the force from object the planet on the sun
  system->bodies[1]->setForce(system->bodies[1]->getForce() - force);
}

void Gravity::potential(System* system)
{
  // Initialise the distance and the potenital energy
  double r = 0;
  vec3 r_vec(0, 0, 0);
  double potential_energy = 0;
  
  // Calculate the potential energy for each object
  for (int i = 0; i < system->bodies.size(); i++) {
    for (int j = i + 1; j < system->bodies.size(); j++) {
      
      // Calculate the distance between object i and j
      r_vec = system->bodies[i]->getPosition() - system->bodies[j]->getPosition();
      r = r_vec.length();
      
      // Calculate the potential energy for object i due to the gravitational field of object j
      potential_energy = - m_G * system->bodies[i]->getMass() * system->bodies[j]->getMass() / (m_solar_mass*r);
      system->bodies[i]->setPotential_energy(system->bodies[i]->getPotential_energy() + potential_energy);
      
      // Use symmetry to calculate the potential energy for object j due to the gravitational field of object i
      system->bodies[j]->setPotential_energy(system->bodies[j]->getPotential_energy() + potential_energy);
      
    }
  }
}

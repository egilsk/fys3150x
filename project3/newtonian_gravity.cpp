#include "newtonian_gravity.h"

NewtonianGravity::NewtonianGravity(double G, double solar_mass)
{
  m_G = G;
  m_solar_mass = solar_mass;
}

void NewtonianGravity::forces(System* system)
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

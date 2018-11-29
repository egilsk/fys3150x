#include "lennard_jones.h"

LennardJones::LennardJones(double epsilon, double sigma)
{
  m_epsilon = epsilon;
  m_sigma = sigma;
}

void LennardJones::forces(System* system)
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
      force = r_vec * (-m_epsilon) * system->bodies[i]->getMass() * system->bodies[j]->getMass() / (m_sigma*pow(r,3.0));
      system->bodies[i]->setForce(system->bodies[i]->getForce() + force);
      
      // Use N3L to calculate the force from object i on j
      system->bodies[j]->setForce(system->bodies[j]->getForce() - force);
      
    }
  }
}

void LennardJones::potential(System* system)
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
      
      // Calculate the potential energy for object i due to the force from object j
      potential_energy = - m_epsilon * system->bodies[i]->getMass() * system->bodies[j]->getMass() / (m_sigma*r);
      system->bodies[i]->setPotential_energy(system->bodies[i]->getPotential_energy() + potential_energy);
      
      // Use symmetry to calculate the potential energy for object j due to the force from object i
      system->bodies[j]->setPotential_energy(system->bodies[j]->getPotential_energy() + potential_energy);
      
    }
  }
}

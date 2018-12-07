#include "lennard_jones.h"

void LennardJones::forces(System* system)
{
  // Initialise the distance, force and potential energy
  double r = 0; double r2 = 0; double r6 = 0; double r12 = 0;
  vec3 r_vec(0, 0, 0);
  vec3 force(0, 0, 0);
  double potential_energy = 0;
  
  // Calculate the forces between the objects and the potential energy
  for (int i = 0; i < system->bodies.size(); i++) {
    for (int j = i + 1; j < system->bodies.size(); j++) {
      
      // Calculate the distance between object i and j
      r_vec = system->bodies[i]->getPosition() - system->bodies[j]->getPosition();
      system->periodicDistance(&r_vec);

      r2 = r_vec.lengthSquared();
      r6 = r2*r2*r2;
      r12 = r6*r6;
      
      // Calculate the force from object j on i
      force = r_vec * (24.0/r2) * ( 2.0/r12 - 1.0/r6 );
      system->bodies[i]->setForce(system->bodies[i]->getForce() + force);
      
      // Use N3L to calculate the force from object i on j
      system->bodies[j]->setForce(system->bodies[j]->getForce() - force);
      
      // Calculate the potential energy between object i and object j
      potential_energy += 4 * (1.0/r12 - 1.0/r6);

    }
  }

  system->setPotential_energy(potential_energy);

}

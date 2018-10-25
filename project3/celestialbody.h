#ifndef CELESTIALBODY_H
#define CELESTIALBODY_H

#include "vec3.h"

class CelestialBody {
  
 private:
  
  // Properties of the body
  string m_name;
  vec3 m_position;
  vec3 m_velocity;
  double m_mass;
  
  vec3 m_force;
  double m_kinetic_energy;
  double m_potential_energy;
  vec3 m_angular_momentum;
  vec3 m_angular_momentum_per_mass;
  
 public:
  
  // Constructor
  CelestialBody(string new_name, vec3 new_position, vec3 new_velocity, double new_mass);
  
  // Destructor
  ~CelestialBody() {};

  // Getters
  string getName() { return m_name; }
  vec3 getPosition() { return m_position; }
  vec3 getVelocity() { return m_velocity; }
  double getMass() { return m_mass; }
  vec3 getForce() { return m_force; }
  double getKinetic_energy() { return m_kinetic_energy; }
  double getPotential_energy() { return m_potential_energy; }
  vec3 getAngular_momentum() { return m_angular_momentum; }
  vec3 getAngular_momentum_per_mass() { return m_angular_momentum_per_mass; }
  
  // Setters
  void setName(string name) { m_name = name; }
  void setPosition(vec3 position) { m_position = position; }
  void setVelocity(vec3 velocity) { m_velocity = velocity; }
  void setMass(double mass) { m_mass = mass; }
  void setForce(vec3 force) { m_force = force; }
  void setPotential_energy(double potential_energy) { m_potential_energy = potential_energy; }

  void setKinetic_energy() { m_kinetic_energy = 0.5*m_mass*m_velocity.lengthSquared(); }
  void setAngular_momentum() { m_angular_momentum = m_position.cross(m_velocity)*m_mass; }
  void setAngular_momentum_per_mass() { m_angular_momentum_per_mass = m_position.cross(m_velocity); }

  // Print function
  void print();

};

#endif // CELESTIALBODY_H

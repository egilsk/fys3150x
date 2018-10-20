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
  
  double m_kinetic_energy;
  double m_potential_energy;
  double m_angular_momentum;
  
 public:
  
  // Constructor
  CelestialBody(string new_name, vec3 new_position, vec3 new_velocity, double new_mass);
  
  // Destructor
  ~CelestialBody() {};

  // Force on the body
  vec3 force;

  // Getters
  string getName() { return m_name; }
  vec3 getPosition() { return m_position; }
  vec3 getVelocity() { return m_velocity; }
  double getMass() { return m_mass; }
  double getKinetic_energy() { return m_kinetic_energy; }
  double getPotential_energy() { return m_potential_energy; }
  double getAngular_momentum() { return m_angular_momentum; }
  
  // Setters
  void setName(string name) { m_name = name; }
  void setPosition(vec3 position) { m_position = position; }
  void setVelocity(vec3 velocity) { m_velocity = velocity; }
  void setMass(double mass) { m_mass = mass; }
  void setKinetic_energy(double kinetic_energy) { m_kinetic_energy = kinetic_energy; }
  void setPotential_energy(double potential_energy) { m_potential_energy = potential_energy; }
  void setAngular_momentum(double angular_momentum) { m_angular_momentum = angular_momentum; }

  // Print function
  void print();

};

#endif // CELESTIALBODY_H

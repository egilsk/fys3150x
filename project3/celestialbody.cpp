#include "celestialbody.h"

CelestialBody::CelestialBody(string new_name, vec3 new_position, vec3 new_velocity, double new_mass): 
  m_name(new_name), m_position(new_position), m_velocity(new_velocity), m_mass(new_mass) {}

void CelestialBody::print()
{
  cout << m_name << " Position: " << m_position << " Velocity: " << m_velocity << endl;
}

#include "atom.h"

Atom::Atom(vec3 new_position, vec3 new_velocity, double new_mass): 
  m_position(new_position), m_velocity(new_velocity), m_mass(new_mass) {}

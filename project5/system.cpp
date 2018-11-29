#include "system.h"

void System::resetForces()
{
  for (CelestialBody* object : bodies) { object->setForce({0,0,0}); }
}

void System::resetPotential()
{
  for (CelestialBody* object : bodies) { object->setPotential_energy(0); }
}

void System::initialiseLattice(int n_cells, double b, double T)
{
  int n_atoms = 4*n_cells;
  double mass;
  vec3 r, v;

  for (int i = 0; i < n_atoms; i++){
    
  }
  
  // Initialise the Sun
  mass = ;
  r(x, y, z);
  v(v_x, v_y, v_z);

  Atom* sun = new CelestialBody("Sun", r_sun, v_sun, mass_sun);
  S.addObject(sun);

}

void System::header(ofstream& ofile, int n)
{
  ofile << setiosflags(ios::showpoint | ios::scientific | ios::left);
  ofile << "Number of points: " << n + 1 << endl;
  ofile << setw(16) << "";
  for (CelestialBody* object : bodies) {
    ofile << setw(48) << object->getName() + ":";
  }
  ofile << endl;
  ofile << setw(16) << "Time";
  for (int i = 0; i < bodies.size(); i++){
    ofile << setw(16) << "Position_(x)";
    ofile << setw(16) << "Position_(y)";
    ofile << setw(16) << "Position_(z)";
  }
  ofile << endl;
}

void System::output(ofstream& ofile, double t)
{
  ofile << setw(16) << t;
  for (CelestialBody* object : bodies) {
    ofile << setw(16) << object->getPosition().x();
    ofile << setw(16) << object->getPosition().y();
    ofile << setw(16) << object->getPosition().z();
  }
  ofile << endl;
}

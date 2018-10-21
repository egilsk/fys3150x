#include "system.h"

void System::resetForces()
{
  for (CelestialBody* object : bodies) { object->force = {0,0,0}; }
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

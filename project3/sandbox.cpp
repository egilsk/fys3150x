#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <string>

#include "vec3.h"
#include "celestialbody.h"
#include "system.h"
#include "gravity.h"
#include "forward_euler.h"

using namespace std;

int main (int argc, char* argv[]){
  
  // Declare the number of steps and the final time
  int n; double T;
  // Read the number of steps and the final time
  if( argc <= 2 ){
    cout << "Error: " << argv[0] << " reads the number of steps and the final time" << endl;
    exit(1);
  }
  else{
    n = atoi(argv[1]);
    T = atof(argv[2]);
  }
  
  // Define the step size
  double h = T/n;
  // Define pi
  double pi = 4.0*atan(1.0);
  // Calculate constant
  double four_pi2 = 4*pi*pi;
  
  // Initialise time
  double t = 0.0;
  
  // Initialise the Sun
  vec3 position_sun(0,0,0);
  vec3 velocity_sun(0,0,0);
  double mass_sun = 2.0e30;

  // Initialise Earth
  vec3 position_earth(1, 0, 0);
  vec3 velocity_earth(0, 2.0*pi, 0);
  double mass_earth = 6.0e24;

  // Initialise Jupiter
  vec3 position_jupiter(5.2, 0, 0);
  vec3 velocity_jupiter(0, 2.0*pi*position_jupiter.x()/12, 0);
  double mass_jupiter = 1.9e27;

  // Initialise the system
  System S;
  
  CelestialBody* sun = new CelestialBody("Sun", position_sun, velocity_sun, mass_sun);
  CelestialBody* earth = new CelestialBody("Earth", position_earth, velocity_earth, mass_earth);
  CelestialBody* jupiter = new CelestialBody("Jupiter", position_jupiter, velocity_jupiter, mass_jupiter);
  
  S.addObject(sun);
  S.addObject(earth);
  S.addObject(jupiter);
  
  // Declare and open outputfile
  ofstream ofile;
  ofile.open("solar_system.dat");
  // Prepare the outfile, and write the number of points
  ofile << setiosflags(ios::showpoint | ios::scientific | ios::left);
  ofile << "Number of points: " << n + 1 << endl;
  ofile << setw(16) << "";
  for (CelestialBody* object : S.bodies) {
    ofile << setw(48) << object->getName() + ":";
  }
  ofile << endl;
  ofile << setw(16) << "Time";
  for (int i = 0; i < S.bodies.size(); i++){
    ofile << setw(16) << "Position_(x)";
    ofile << setw(16) << "Position_(y)";
    ofile << setw(16) << "Position_(z)";
  }
  ofile << endl;
  ofile << setw(16) << t;
  for (CelestialBody* object : S.bodies) {
    ofile << setw(16) << object->getPosition().x();
    ofile << setw(16) << object->getPosition().y();
    ofile << setw(16) << object->getPosition().z();
  }
  ofile << endl;

  // Initialise the force and the solver
  Gravity F(four_pi2, mass_sun);
  ForwardEuler solver;  

  // Run the calculations
  while (t < T) {
    S.resetForces();
    F.forces(&S);
    solver.integrate(&S, h);
    t += h;

    ofile << setw(16) << t;
    for (CelestialBody* object : S.bodies) {
      ofile << setw(16) << object->getPosition().x();
      ofile << setw(16) << object->getPosition().y();
      ofile << setw(16) << object->getPosition().z();
    }
    ofile << endl;
  }
  return 0;
}

#include <cmath>

#include "vec3.h"
#include "celestialbody.h"
#include "system.h"
#include "gravity.h"
#include "forward_euler.h"
#include "velocity_verlet.h"

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
  vec3 r_sun(-6.28e-3, 5.98e-3, 1.46e-4);
  vec3 v_sun = vec3(-6.16e-6, -5.57e-6, 1.79e-7)*365;
  double mass_sun = 1.99e30;

  // Initialise Mercury
  vec3 r_mercury(-3.96e-1, -1.06e-2, 3.45e-2);
  vec3 v_mercury = vec3(-4.66e-3, -2.69e-2, -1.77e-3)*365;
  double mass_mercury = 3.30e23;

  // Initialise Venus
  vec3 r_venus(-1.97e-1, -6.94e-1, 1.61e-3);
  vec3 v_venus = vec3(1.94e-2, -5.41e-3, -1.19e-3)*365;
  double mass_venus = 4.87e24;

  // Initialise Earth
  vec3 r_earth(-4.68e-1, 8.75e-1, 1.54e-4);
  vec3 v_earth = vec3(-1.55e-2, -8.15e-3, 4.84e-7)*365;
  double mass_earth = 5.97e24;

  // Initialise Mars
  vec3 r_mars(-1.47, 8.07e-1, 5.28e-2);
  vec3 v_mars = vec3(-6.21e-3, -1.11e-2, -7.93e-5)*365;
  double mass_mars = 6.42e23;

  // Initialise Jupiter
  vec3 r_jupiter(2.51, -4.46, -3.78e-2);
  vec3 v_jupiter = vec3(6.47e-3, 4.06e-3, -1.62e-4)*365;
  double mass_jupiter = 1.90e27;

  // Initialise Saturn
  vec3 r_saturn(9.36, 1.30, -3.95e-1);
  vec3 v_saturn = vec3(-1.06e-3, 5.52e-3, -5.38e-5)*365;
  double mass_saturn = 5.68e26;

  // Initialise Uranus
  vec3 r_uranus(1.12e1, -1.63e1, -2.06e-1);
  vec3 v_uranus = vec3(3.21e-3, 2.05e-3, -3.40e-5)*365;
  double mass_uranus = 8.68e25;

  // Initialise Neptun
  vec3 r_neptun(1.39e1, -2.67e1, 2.30e-1);
  vec3 v_neptun = vec3(2.76e-3, 1.47e-3, -9.38e-5)*365;
  double mass_neptun = 1.02e26;

  // Initialise Pluto
  vec3 r_pluto(-1.31e1, -2.61e1, 6.58);
  vec3 v_pluto = vec3(2.90e-3, -1.87e-3, -6.52e-4)*365;
  double mass_pluto = 1.31e22;

  // Initialise the system
  System S;
  
  CelestialBody* sun = new CelestialBody("Sun", r_sun, v_sun, mass_sun);
  CelestialBody* mercury = new CelestialBody("Mercury", r_mercury, v_mercury, mass_mercury);
  CelestialBody* venus = new CelestialBody("Venus", r_venus, v_venus, mass_venus);
  CelestialBody* earth = new CelestialBody("Earth", r_earth, v_earth, mass_earth);
  CelestialBody* mars = new CelestialBody("Mars", r_mars, v_mars, mass_mars);
  CelestialBody* jupiter = new CelestialBody("Jupiter", r_jupiter, v_jupiter, mass_jupiter);
  CelestialBody* saturn = new CelestialBody("Saturn", r_saturn, v_saturn, mass_saturn);  
  CelestialBody* uranus = new CelestialBody("Uranus", r_uranus, v_uranus, mass_uranus);
  CelestialBody* neptun = new CelestialBody("Neptun", r_neptun, v_neptun, mass_neptun);
  CelestialBody* pluto = new CelestialBody("Pluto", r_pluto, v_pluto, mass_pluto);  

  S.addObject(sun);
  //S.addObject(mercury);
  //S.addObject(venus);
  S.addObject(earth);
  //S.addObject(mars);
  S.addObject(jupiter);
  //S.addObject(saturn);
  //S.addObject(uranus);
  //S.addObject(neptun);
  //S.addObject(pluto);
  
  // Declare and open output file
  ofstream ofile;
  ofile.open("solar_system.dat");
  
  // Create header and write out the starting positions
  S.header(ofile, n);
  S.output(ofile, t);

  // Initialise the force and the solver
  Gravity F(four_pi2, mass_sun);
  VelocityVerlet solver;

  // Calculate the initial force (Verlet)
  F.newtonianForces(&S);

  // Calculate the constant h/(mass*2) (Verlet)
  vector<double> h_mass_two;
  for (int i = 0; i < S.bodies.size(); i++) {
    h_mass_two.push_back(h/(S.bodies[i]->getMass()*2));
  }

  // Declare a vector storing the forces (Verlet)
  vector<vec3> forces_temp;

  // Run the calculations
  while (t < T) {
    
    // Store current forces
    forces_temp = solver.storeForces(&S);

    // Update position
    solver.updatePosition(&S, h, h_mass_two);
    
    // Update forces
    S.resetForces();
    F.newtonianForces(&S);
    
    // Update velocity
    solver.updateVelocity(&S, h, h_mass_two, forces_temp);
    
    // Update time
    t += h;

    // Write to file
    S.output(ofile, t);
  }
  
  ofile.close();
  
  return 0;
}

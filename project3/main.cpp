#include <cmath>

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
  vec3 r_sun(0,0,0);
  vec3 v_sun(0,0,0);
  double mass_sun = 2.0e30;

  // Initialise Mercury
  vec3 r_mercury(0.39,0,0);
  vec3 v_mercury(0,2.0*pi*r_mercury.x()*365/88,0);
  double mass_mercury = 3.3e23;

  // Initialise Venus
  vec3 r_venus(0.72,0,0);
  vec3 v_venus(0,2.0*pi*r_venus.x()*365/225,0);
  double mass_venus = 4.9e24;

  // Initialise Earth
  vec3 r_earth(1.0, 0, 0);
  vec3 v_earth(0, 2.0*pi, 0);
  double mass_earth = 6.0e24;

  // Initialise Mars
  vec3 r_mars(1.52,0,0);
  vec3 v_mars(0,2.0*pi*r_mars.x()*365/687,0);
  double mass_mars = 6.6e23;

  // Initialise Jupiter
  vec3 r_jupiter(5.2, 0, 0);
  vec3 v_jupiter(0, 2.0*pi*r_jupiter.x()/12, 0);
  double mass_jupiter = 1.9e27;

  // Initialise Saturn
  vec3 r_saturn(9.54,0,0);
  vec3 v_saturn(0,2.0*pi*r_saturn.x()/29,0);
  double mass_saturn = 5.5e26;

  // Initialise Uranus
  vec3 r_uranus(19.19,0,0);
  vec3 v_uranus(0,2.0*pi*r_uranus.x()/84,0);
  double mass_uranus = 8.8e25;

  // Initialise Neptun
  vec3 r_neptun(30.06,0,0);
  vec3 v_neptun(0,2.0*pi*r_neptun.x()/165,0);
  double mass_neptun = 1.03e26;

  // Initialise Pluto
  vec3 r_pluto(39.53,0,0);
  vec3 v_pluto(0,2.0*pi*r_pluto.x()/248,0);
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
  S.addObject(mercury);
  S.addObject(venus);
  S.addObject(earth);
  S.addObject(mars);
  S.addObject(jupiter);
  S.addObject(saturn);
  S.addObject(uranus);
  S.addObject(neptun);
  S.addObject(pluto);
  
  // Declare and open output file
  ofstream ofile;
  ofile.open("solar_system.dat");
  
  // Create header and write out the starting positions
  S.header(ofile, n);
  S.output(ofile, t);

  // Initialise the force and the solver
  Gravity F(four_pi2, mass_sun);
  ForwardEuler solver;

  // Run the calculations
  while (t < T) {
    S.resetForces();
    F.forces(&S);
    solver.integrate(&S, h);
    t += h;

    S.output(ofile, t);
  }

  ofile.close();

  return 0;
}

#include "vec3.h"
#include "celestialbody.h"
#include "system.h"
#include "gravity.h"
#include "velocity_verlet.h"

using namespace std;

int main (int argc, char* argv[]) {
  
  // Declare the number of steps
  int n;
  // Read the number of steps
  if( argc <= 1 ){
    cout << "Error: " << argv[0] << " reads the number of steps" << endl;
    exit(1);
  }
  else{
    n = atoi(argv[1]);
  }

  // Define the total time
  double T = 100.0; 
  // Define the step size
  double h = T/n;

  // Define pi
  double pi = 4.0*atan(1.0);
  // Define speed of light
  double c = 63240;
  // Calculate constant
  double four_pi2 = 4*pi*pi;
  
  // Initialise time
  double t = 0.0;

  // Initialise the system
  System S;

  // Initialise Mercury
  double mass_mercury = 3.30e23;
  vec3 r_mercury(0.3075, 0, 0);
  vec3 v_mercury = vec3(0, 12.44, 0);
  
  CelestialBody* mercury = new CelestialBody("Mercury", r_mercury, v_mercury, mass_mercury);
  S.addObject(mercury);

  // Initialise the Sun
  double mass_sun = 1.99e30;
  vec3 r_sun(0, 0, 0);
  vec3 v_sun = mercury->getVelocity() * -mass_mercury/mass_sun;

  CelestialBody* sun = new CelestialBody("Sun", r_sun, v_sun, mass_sun);
  S.addObject(sun);
 
  // Declare and open output file
  ofstream ofile;
  ofile.open("mercury.dat");

  // Initialise the force and the solver
  Gravity F(four_pi2, mass_sun, c);
  VelocityVerlet solver;

  // Calculate the initial force
  F.relativisticForces(&S);

  // Calculate the constant h/(mass*2) 
  vector<double> h_mass_two;
  for (int i = 0; i < S.bodies.size(); i++) {
    h_mass_two.push_back(h/(S.bodies[i]->getMass()*2));
  }

  // Declare a vector storing the forces and a vec3 storing the distance
  vector<vec3> forces_temp;
  vec3 r_temp(0, 0, 0);

  // Declare theta_p and number of orbits
  double theta_p;   
  int orbits = 0;

  // Run the calculations
  while (t < T) {
    
    r_temp = mercury->getPosition();
    forces_temp = solver.storeForces(&S);
    
    solver.updatePosition(&S, h, h_mass_two);
    
    S.resetForces();
    F.relativisticForces(&S);
    
    solver.updateVelocity(&S, h, h_mass_two, forces_temp);
    
    t += h;
    
    // Check if the distance from the sun decreases
    while (mercury->getPosition().length() - r_temp.length() < 0) {
      
      r_temp = mercury->getPosition();
      forces_temp = solver.storeForces(&S);
      
      solver.updatePosition(&S, h, h_mass_two);
      
      S.resetForces();
      F.relativisticForces(&S);
      
      solver.updateVelocity(&S, h, h_mass_two, forces_temp);
      
      t += h;

      // Check if the distance from the sun increases
      if (mercury->getPosition().length() - r_temp.length() > 0) {
	
	// Calculate theta_p and write to file
	theta_p = atan(r_temp.y()/r_temp.x())*180/pi*3600;
	ofile << theta_p << endl;
	
	// Count the number of orbits
	orbits += 1;
	
      } else {
      }
    }

  }
  
  ofile.close();
  
  cout << orbits << endl;

  return 0;
}

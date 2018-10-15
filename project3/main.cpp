#include "verlet.h"

using namespace std;

int main(int argc, char *argv[]){
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

  // Define pi
  double pi = 4*atan(1);

  // Initialise Earth
  double mass_earth = 6.0e24;
  double x_earth = 0.929; double y_earth = 0.37;
  double vx_earth = -6.55e-3*365; double vy_earth = 1.596e-2*365;

  // Initialise Jupiter
  double mass_jupiter = 1.9e27;
  double x_jupiter = -2.65; double y_jupiter = -4.66;
  double vx_jupiter = 6.467e-3*365; double vy_jupiter = -3.37e-3*365;

  Verlet(n, T, mass_earth, x_earth, y_earth, vx_earth, vy_earth, mass_jupiter, x_jupiter, y_jupiter, vx_jupiter, vy_jupiter);

  return 0;
}

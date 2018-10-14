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
  double x_earth = 1.0; double y_earth = 0.0;
  double vx_earth = 0.0; double vy_earth = 2.0*pi;

  // Initialise Jupiter
  double mass_jupiter = 1.9e27;
  double x_jupiter = 5.2; double y_jupiter = 0.0;
  double vx_jupiter = 0.0; double vy_jupiter = 2.0*pi*x_jupiter/12;

  Verlet(n, T, mass_earth, x_earth, y_earth, vx_earth, vy_earth, mass_jupiter, x_jupiter, y_jupiter, vx_jupiter, vy_jupiter);

  return 0;
}

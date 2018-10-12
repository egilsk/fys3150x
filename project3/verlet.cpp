#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>

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

  // Define the step size 
  double h = T/n;

  // Define pi
  double pi = 4*atan(1);
  // Calculate constant
  double two_pi2_h = 2*pi*pi*h;

  // Initialise the time, position and velocity
  double t = 0.0;
  double x = 1.0; double y = 0.0; double r = sqrt(x*x + y*y);
  double v_x = 0.0; double v_y = 2*pi;

  // Declare and open outputfile
  ofstream ofile;
  ofile.open("earth_sun_verlet.dat");
  // Write out the number of points, and the first point
  ofile << setiosflags(ios::showpoint | ios::scientific);
  ofile << "Number of points: " << n + 1 << endl;
  ofile << "  Time            " << "x-coordinate    " << "y-coordinate    " << "distance        " << "velocity (x)    " << "velocity (y)" << endl;
  ofile << setw(16) << setprecision(8) << t;
  ofile << setw(16) << setprecision(8) << x;
  ofile << setw(16) << setprecision(8) << y;
  ofile << setw(16) << setprecision(8) << r;
  ofile << setw(16) << setprecision(8) << v_x;
  ofile << setw(16) << setprecision(8) << v_y << endl;

  // Velocity Verlet method
  double x_new; double y_new; double r_new; double r3; double r_new3;
  while (t < T){
    r3 = pow(r, 3.0);
    x_new = x + h*(v_x - two_pi2_h*x/r3);
    y_new = y + h*(v_y - two_pi2_h*y/r3);
    r_new = sqrt(x_new*x_new + y_new*y_new);
    r_new3 = pow(r_new, 3.0);
    v_x -= two_pi2_h*(x/r3 + x_new/r_new3);
    v_y -= two_pi2_h*(y/r3 + y_new/r_new3);
    x = x_new; y = y_new; r = r_new;
    t += h;
    ofile << setw(16) << setprecision(8) << t;
    ofile << setw(16) << setprecision(8) << x;
    ofile << setw(16) << setprecision(8) << y;
    ofile << setw(16) << setprecision(8) << r;
    ofile << setw(16) << setprecision(8) << v_x;
    ofile << setw(16) << setprecision(8) << v_y << endl;
  }

  return 0;
}

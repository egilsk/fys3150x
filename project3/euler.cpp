#include "euler.h"

using namespace std;

// The forward Euler method
void Euler(int n, double T, double mass_earth, double x, double y, double v_x, double v_y){

  // Define the step size
  double h = T/n;
  // Define pi
  double pi = 4*atan(1);
  // Calculate constant
  double four_pi2_h = 4*pi*pi*h;

  // Initialise time
  double t = 0.0;
  // Calculate the initial speed and distance
  double v = sqrt(v_x*v_x + v_y*v_y);
  double r = sqrt(x*x + y*y);

  // Declare and open outputfile
  ofstream ofile;
  ofile.open("earth_sun_euler.dat");
  // Write out the number of points, and the first point
  ofile << setiosflags(ios::showpoint | ios::scientific);
  ofile << "Number of points: " << n + 1 << endl;
  ofile << "" << endl;
  ofile << "  Time            " << "Position_(x)    " << "Position_(y)    " << "Distance        " << "Velocity_(x)    " << "Velocity_(y)    " << "Speed           " << endl;
  ofile << setw(16) << setprecision(8) << t;
  ofile << setw(16) << setprecision(8) << x;
  ofile << setw(16) << setprecision(8) << y;
  ofile << setw(16) << setprecision(8) << r;
  ofile << setw(16) << setprecision(8) << v_x;
  ofile << setw(16) << setprecision(8) << v_y;
  ofile << setw(16) << setprecision(8) << v << endl;

  // Euler's method (forward)
  double x_temp; double y_temp; double r3;
  while (t < T){
    
    // Calculate new position
    x_temp = x + h*v_x;
    y_temp = y + h*v_y;
    
    // Update velocity and speed
    r3 = r*r*r;
    v_x -= four_pi2_h*x/r3;
    v_y -= four_pi2_h*y/r3;
    v = sqrt(v_x*v_x + v_y*v_y);

    // Update time
    t += h;
    
    // Update position and distance
    x = x_temp; y = y_temp;
    r = sqrt(x*x + y*y);

    // Write to file
    ofile << setw(16) << setprecision(8) << t;
    ofile << setw(16) << setprecision(8) << x;
    ofile << setw(16) << setprecision(8) << y;
    ofile << setw(16) << setprecision(8) << r;
    ofile << setw(16) << setprecision(8) << v_x;
    ofile << setw(16) << setprecision(8) << v_y;
    ofile << setw(16) << setprecision(8) << v << endl;
  }

}

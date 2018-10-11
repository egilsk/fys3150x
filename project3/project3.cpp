#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main(int argc, char *argv[]){

  // Define number of steps, total time and step size h 
  int n = 1000;
  double T = 10.0;
  double h = T/n;

  // Define pi
  double pi = 4*atan(1);
  // Calculate constant
  double four_pi2_h = 4*pi*pi*h;

  // Initalize the time, position, and velocity
  double t = 0.0;
  double x = 1.0; double y = 0.0; double r = sqrt(x*x + y*y);
  double v_x = 0.0; double v_y = 2*pi;

  // Declare and open outputfile
  ofstream ofile;
  ofile.open("earth_sun.dat");
  // Write out the number of points, and the first point
  ofile << setiosflags(ios::showpoint | ios::scientific);
  ofile << "Number of steps: " << n + 1 << endl;
  ofile << "  Time            " << "x-coordinate    " << "y-coordinate    " << "velocity (x)    " << "velocity (y)" << endl;
  ofile << setw(16) << setprecision(8) << t;
  ofile << setw(16) << setprecision(8) << x;
  ofile << setw(16) << setprecision(8) << y;
  ofile << setw(16) << setprecision(8) << v_x;
  ofile << setw(16) << setprecision(8) << v_y << endl;

  // Euler's method
  double x_new; double y_new; double r3;
  while (t < T){
    x_new = x + h*v_x;
    y_new = y + h*v_y;
    r3 = r*r*r;
    v_x -= four_pi2_h*x/r3;
    v_y -= four_pi2_h*y/r3;
    x = x_new; y = y_new;
    r = sqrt(x*x + y*y);
    t += h;
    ofile << setw(16) << setprecision(8) << t;
    ofile << setw(16) << setprecision(8) << x;
    ofile << setw(16) << setprecision(8) << y;
    ofile << setw(16) << setprecision(8) << v_x;
    ofile << setw(16) << setprecision(8) << v_y << endl;
  }

  return 0;
}

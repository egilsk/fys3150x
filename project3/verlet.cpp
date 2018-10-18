#include "verlet.h"

using namespace std;

// The velocity Verlet method
void Verlet(int n, double T, double m_e, double x_e, double y_e, double vx_e, double vy_e, double m_j, double x_j, double y_j, double vx_j, double vy_j){

  // Define the step size
  double h = T/n;
  // Define pi
  double pi = 4*atan(1);
  // Calculate constant
  double two_pi2_h = 2*pi*pi*h;
  // Define the solar mass
  double m_sun = 2.0e30;

  // Initialise time
  double t = 0.0;
  // Calculate the initial speeds and distances
  double v_e = sqrt(vx_e*vx_e + vy_e*vy_e);
  double r_e = sqrt(x_e*x_e + y_e*y_e);
  double v_j = sqrt(vx_j*vx_j + vy_j*vy_j);
  double r_j = sqrt(x_j*x_j + y_j*y_j);  
  double r_ej = sqrt((x_j - x_e)*(x_j - x_e) + (y_j - y_e)*(y_j - y_e));

  // Declare and open outputfile
  ofstream ofile;
  ofile.open("solar_system.dat");
  // Write out the number of points, and the first point
  ofile << setiosflags(ios::showpoint | ios::scientific);
  ofile << "Number of points: " << n + 1 << endl;
  ofile << "  Earth:";
  ofile << setw(114) << "Jupiter:" << endl;
  ofile << "  Time            " << "Position_(x)    " << "Position_(y)    " << "Distance        " << "Velocity_(x)    " << "Velocity_(y)    " << "Speed           ";
  ofile << "Position_(x)    " << "Position_(y)    " << "Distance        " << "Velocity_(x)    " << "Velocity_(y)    " << "Speed           " << endl;
  ofile << setw(16) << setprecision(8) << t;
  ofile << setw(16) << setprecision(8) << x_e;
  ofile << setw(16) << setprecision(8) << y_e;
  ofile << setw(16) << setprecision(8) << r_e;
  ofile << setw(16) << setprecision(8) << vx_e;
  ofile << setw(16) << setprecision(8) << vy_e;
  ofile << setw(16) << setprecision(8) << v_e;
  ofile << setw(16) << setprecision(8) << x_j;
  ofile << setw(16) << setprecision(8) << y_j;
  ofile << setw(16) << setprecision(8) << r_j;
  ofile << setw(16) << setprecision(8) << vx_j;
  ofile << setw(16) << setprecision(8) << vy_j;
  ofile << setw(16) << setprecision(8) << v_j << endl;

  // Velocity Verlet method
  double r_e3; double r_j3; double r_ej3;
  double x_e_new; double y_e_new; double r_e_new; double r_e_new3;
  double x_j_new; double y_j_new; double r_j_new; double r_j_new3;
  double r_ej_new; double r_ej_new3;
  while (t < T){
    r_e3 = pow(r_e, 3.0);
    r_j3 = pow(r_j, 3.0);
    r_ej3 = pow(r_ej, 3.0);

    x_e_new = x_e + h*(vx_e - two_pi2_h*(x_e/r_e3 + m_j/m_sun*(x_e - x_j)/r_ej3));
    y_e_new = y_e + h*(vy_e - two_pi2_h*(y_e/r_e3 + m_j/m_sun*(y_e - y_j)/r_ej3));
    r_e_new = sqrt(x_e_new*x_e_new + y_e_new*y_e_new);
    r_e_new3 = pow(r_e_new, 3.0);

    x_j_new = x_j + h*(vx_j - two_pi2_h*(x_j/r_j3 + m_e/m_sun*(x_j - x_e)/r_ej3));
    y_j_new = y_j + h*(vy_j - two_pi2_h*(y_j/r_j3 + m_e/m_sun*(y_j - y_e)/r_ej3));
    r_j_new = sqrt(x_j_new*x_j_new + y_j_new*y_j_new);
    r_j_new3 = pow(r_j_new, 3.0);

    r_ej_new = sqrt((x_j_new - x_e_new)*(x_j_new - x_e_new) + (y_j_new - y_e_new)*(y_j_new - y_e_new));
    r_ej_new3 = pow(r_ej_new, 3.0);

    vx_e -= two_pi2_h*(x_e/r_e3 + x_e_new/r_e_new3 + m_j/m_sun*((x_e - x_j)/r_ej3 + (x_e_new - x_j_new)/r_ej_new3));
    vy_e -= two_pi2_h*(y_e/r_e3 + y_e_new/r_e_new3 + m_j/m_sun*((y_e - y_j)/r_ej3 + (y_e_new - y_j_new)/r_ej_new3));
    v_e = sqrt(vx_e*vx_e + vy_e*vy_e);
    
    vx_j -= two_pi2_h*(x_j/r_j3 + x_j_new/r_j_new3 + m_e/m_sun*((x_j - x_e)/r_ej3 + (x_j_new - x_e_new)/r_ej_new3));
    vy_j -= two_pi2_h*(y_j/r_j3 + y_j_new/r_j_new3 + m_e/m_sun*((y_j - y_e)/r_ej3 + (y_j_new - y_e_new)/r_ej_new3));
    v_j = sqrt(vx_j*vx_j + vy_j*vy_j);

    x_e = x_e_new; y_e = y_e_new; r_e = r_e_new;
    x_j = x_j_new; y_j = y_j_new; r_j = r_j_new;
    r_ej = r_ej_new;

    t += h;

    ofile << setw(16) << setprecision(8) << t;
    ofile << setw(16) << setprecision(8) << x_e;
    ofile << setw(16) << setprecision(8) << y_e;
    ofile << setw(16) << setprecision(8) << r_e;
    ofile << setw(16) << setprecision(8) << vx_e;
    ofile << setw(16) << setprecision(8) << vy_e;
    ofile << setw(16) << setprecision(8) << v_e;
    ofile << setw(16) << setprecision(8) << x_j;
    ofile << setw(16) << setprecision(8) << y_j;
    ofile << setw(16) << setprecision(8) << r_j;
    ofile << setw(16) << setprecision(8) << vx_j;
    ofile << setw(16) << setprecision(8) << vy_j;
    ofile << setw(16) << setprecision(8) << v_j << endl;
  }
}

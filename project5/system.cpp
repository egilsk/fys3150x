#include "system.h"

void System::resetForces()
{
  for (Atom* object : bodies) { object->setForce({0,0,0}); }
}

void System::resetPotential()
{
  for (Atom* object : bodies) { object->setPotential_energy(0); }
}

void System::initialiseLattice(int n_cells, double b, double T)
{
  int n_atoms = 4*n_cells*n_cells*n_cells;
  double mass = 39.948;

  arma::mat positions = arma::zeros<arma::mat>(3,n_atoms);

  int i_atom = 0;

  for (int i = 0; i < n_cells; i++){
    for (int j = 0; j < n_cells; j++){
      for (int k = 0; k < n_cells; k++){
	
	positions.col(i_atom) = vec3(i*b, j*b, k*b);
	i_atom += 1;
	positions.col(i_atom) = vec3((i+0.5)*b, (j+0.5)*b, k*b);
	i_atom += 1;
	positions.col(i_atom) = vec3(i*b, (j+0.5)*b, (k+0.5)*b);
	i_atom += 1;
	positions.col(i_atom) = vec3((i+0.5)*b, j*b, (k+0.5)*b);
	i_atom += 1;

      }
    }
  }

  for (int i = 0; i < n_atoms){

    vec3 r(positions(0,i), positions(1,i), positions(2,i)); 
    
    double v_x = 0;
    double v_y = 0;
    double v_z = 0;

    vec3 v(v_x, v_y, v_z);

    Atom* atom = new Atom(r, v, mass);
    this->addObject(atom);
    
  }
  
}

void System::header(ofstream& ofile, int n)
{
  ofile << setiosflags(ios::showpoint | ios::scientific | ios::left);
  ofile << "Number of points: " << n + 1 << endl;
  ofile << setw(16) << "";
  for (Atom* object : bodies) {
    ofile << setw(48) << object->getName() + ":";
  }
  ofile << endl;
  ofile << setw(16) << "Time";
  for (int i = 0; i < bodies.size(); i++){
    ofile << setw(16) << "Position_(x)";
    ofile << setw(16) << "Position_(y)";
    ofile << setw(16) << "Position_(z)";
  }
  ofile << endl;
}

void System::output(ofstream& ofile, double t)
{
  ofile << setw(16) << t;
  for (Atom* object : bodies) {
    ofile << setw(16) << object->getPosition().x();
    ofile << setw(16) << object->getPosition().y();
    ofile << setw(16) << object->getPosition().z();
  }
  ofile << endl;
}

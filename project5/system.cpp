#include "system.h"

void System::resetForces()
{
  for (Atom* object : bodies) { object->setForce({0,0,0}); }
}

void System::resetPotential()
{
  for (Atom* object : bodies) { object->setPotential_energy(0); }
}

void System::initialiseLattice(int n_cells, double b, double m, double T)
{
  int n_atoms = 4*n_cells*n_cells*n_cells;

  vec3 r, v;
  Atom* atom;

  for (int i = 0; i < n_cells; i++){
    for (int j = 0; j < n_cells; j++){
      for (int k = 0; k < n_cells; k++){
	
	r = vec3(i*b, j*b, k*b);
	v = vec3(0, 0, 0);
	
	atom = new Atom(r, v, m);
	this->addObject(atom);
	
	
	r = vec3((i+0.5)*b, (j+0.5)*b, k*b);
	v = vec3(0,0,0);

	atom = new Atom(r, v, m);
	this->addObject(atom);
	

        r = vec3(i*b, (j+0.5)*b, (k+0.5)*b);
	v = vec3(0,0,0);	

	atom = new Atom(r, v, m);
	this->addObject(atom);
	
	
	r = vec3((i+0.5)*b, j*b, (k+0.5)*b);
	v = vec3(0,0,0);	

	atom = new Atom(r, v, m);
	this->addObject(atom);
	
      }
    }
  }

}

void System::periodic(int n_cells, double b)
{
  double size = n_cells*b;

  for (Atom* object : bodies) {

    object->setX( object->getX() - floor( object->getX()/size )*size );
    object->setY( object->getY() - floor( object->getY()/size )*size );
    object->setZ( object->getZ() - floor( object->getZ()/size )*size );
    
  }
}

void System::output(ofstream& ofile, int n_cells)
{
  ofile << setw(16) << 4*n_cells*n_cells*n_cells << endl;
  ofile << endl;
  for (Atom* object : bodies) {
    ofile << setw(16) << object->getPosition().x();
    ofile << setw(16) << object->getPosition().y();
    ofile << setw(16) << object->getPosition().z() << endl;
  }
  ofile << endl;
}

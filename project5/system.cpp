#include "system.h"

System::System(int n_cells, double b):
  m_n_cells(n_cells), m_b(b), m_n_atoms(4*m_n_cells*m_n_cells*m_n_cells), m_size(m_n_cells*m_b) {}

void System::resetForces()
{
  for (Atom* object : bodies) { object->setForce({0,0,0}); }
}

void System::resetMomentum()
{

  vec3 net_velocity(0, 0, 0);
  
  for (Atom* object : bodies) {

    net_velocity += object->getVelocity();

  }

  net_velocity /= bodies.size();

  for (Atom* object : bodies) {

    object->setVelocity( object->getVelocity() - net_velocity );
    
  }

}

void System::initialiseLattice(double m, double T)
{
  double std_dev = sqrt(T/m);

  // Initialise the seed generator
  //random_device rd;
  // Call the Mersenne Twister generator
  mt19937_64 gen(1997);
  // Set up the uniform distribution
  normal_distribution<double> distribution(0.0, std_dev);

  vec3 r, v;
  Atom* atom;

  for (int i = 0; i < m_n_cells; i++){
    for (int j = 0; j < m_n_cells; j++){
      for (int k = 0; k < m_n_cells; k++){
	
	r = vec3(i*m_b, j*m_b, k*m_b);
	v = vec3(distribution(gen), distribution(gen), distribution(gen));
	
	atom = new Atom(r, v, m);
	this->addObject(atom);
	
	
	r = vec3((i+0.5)*m_b, (j+0.5)*m_b, k*m_b);
	v = vec3(distribution(gen), distribution(gen), distribution(gen));

	atom = new Atom(r, v, m);
	this->addObject(atom);
	

        r = vec3(i*m_b, (j+0.5)*m_b, (k+0.5)*m_b);
	v = vec3(distribution(gen), distribution(gen), distribution(gen));	

	atom = new Atom(r, v, m);
	this->addObject(atom);
	
	
	r = vec3((i+0.5)*m_b, j*m_b, (k+0.5)*m_b);
	v = vec3(distribution(gen), distribution(gen), distribution(gen));	

	atom = new Atom(r, v, m);
	this->addObject(atom);
	
      }
    }
  }

}

void System::periodicPosition()
{
  for (Atom* object : bodies) {

    object->setX( object->getX() - floor( object->getX()/m_size )*m_size );
    object->setY( object->getY() - floor( object->getY()/m_size )*m_size );
    object->setZ( object->getZ() - floor( object->getZ()/m_size )*m_size );
    
  }
}

void System::periodicDistance(vec3* r_ij)
{
  double x = r_ij->x() - nearbyint( r_ij->x()/m_size )*m_size;
  double y = r_ij->y() - nearbyint( r_ij->y()/m_size )*m_size;
  double z = r_ij->z() - nearbyint( r_ij->z()/m_size )*m_size;

  r_ij->setXYZ(x,y,z);

}

void System::output(ofstream& ofile)
{
  ofile << setw(16) << m_n_atoms << endl;
  ofile << endl;
  for (Atom* object : bodies) {
    ofile << setw(16) << "Ar";
    ofile << setw(16) << object->getPosition().x();
    ofile << setw(16) << object->getPosition().y();
    ofile << setw(16) << object->getPosition().z() << endl;
  }

}

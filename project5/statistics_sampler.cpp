#include "statistics_sampler.h"

void StatisticsSampler::sampleKinetic_energy(System* system)
{
  double kinetic_energy = 0;
  
  for (Atom* object : system->bodies) {
    
    kinetic_energy += 0.5*object->getMass()*object->getVelocity().lengthSquared();
    
  }

  m_kinetic_energy = kinetic_energy;
  
}

void StatisticsSampler::samplePotential_energy(System* system)
{
  m_potential_energy = system->getPotential_energy();
}

void StatisticsSampler::sampleTemperature(System* system)
{
  m_temperature = 2.0*m_kinetic_energy/(3.0*system->getN_atoms());
}

void StatisticsSampler::sample(System* system)
{
  sampleKinetic_energy(system);
  samplePotential_energy(system);
  sampleTemperature(system);

}

void StatisticsSampler::header(ofstream& ofile, int n_steps)
{
  ofile << setiosflags(ios::showpoint | ios::scientific | ios::left);
  ofile << "Number of time steps: " << n_steps << endl;
  
  ofile << setw(16) << "Time";
  ofile << setw(16) << "Kinetic Energy";
  ofile << setw(16) << "Potential Energy";
  ofile << setw(16) << "Temperature" << endl;
}

void StatisticsSampler::output(ofstream& ofile, double t)
{
  ofile << setw(16) << t;
  ofile << setw(16) << m_kinetic_energy;
  ofile << setw(16) << m_potential_energy;
  ofile << setw(16) << m_temperature << endl;

}

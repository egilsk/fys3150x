#include "statistics_sampler.h"

void StatisticsSampler::sampleKinetic_energy(System system)
{
  double kinetic_energy = 0;
  
  for (Atom* object : system.bodies) {
    
    kinetic_energy += 0.5*object->getMass()*object->getVelocity().lengthSquared();
    
  }

  m_kinetic_energy = kinetic_energy;
  
}

void StatisticsSampler::samplePotential_energy(System system)
{
  m_potential_energy = system.getPotential_energy();
}

void StatisticsSampler::sampleTotal_energy(System system)
{
  m_total_energy = m_kinetic_energy + m_potential_energy;
}

void StatisticsSampler::sampleTemperature(System system)
{
  m_temperature = 2.0*m_kinetic_energy/(3.0*system.getN_atoms());
}

void StatisticsSampler::sample(System system, double t)
{
  sampleKinetic_energy(system);
  samplePotential_energy(system);
  sampleTotal_energy(system);
  sampleD(system, t);
  sampleTemperature(system);

}

void StatisticsSampler::sampleD(System system, double t)
{
  vec3 distance(0,0,0);
  double displacement = 0;

  for (Atom* object : system.bodies) {
    
    distance = object->getPosition() - object->getInitial_position();
    system.periodicDistance(&distance);
    
    displacement += distance.lengthSquared();
    
  }

  displacement /= system.bodies.size();

  m_D = displacement/(6*t);

}

void StatisticsSampler::header(ofstream& ofile, int n_steps, double temperature_initial, double epsilon, double k_B)
{
  ofile << setiosflags(ios::showpoint | ios::scientific | ios::left);
  ofile << "Number of time steps: " << n_steps << endl;
  ofile << "Initial temperature [K]: " << temperature_initial*epsilon/k_B << endl;
  
  ofile << setw(30) << "Time [ps]";
  ofile << setw(30) << "Kinetic Energy [epsilon]";
  ofile << setw(30) << "Potential Energy [epsilon]";
  ofile << setw(30) << "Total Energy [epsilon]";
  ofile << setw(30) << "Temperature [K]";
  ofile << setw(30) << "Diffusion constant [sigma*sqrt(epsilon/u)]" << endl;
}

void StatisticsSampler::output(ofstream& ofile, double t, double sigma, double epsilon, double u, double k_B)
{
  ofile << setw(30) << t*sigma*sqrt(u/epsilon)*1e12;
  ofile << setw(30) << m_kinetic_energy;
  ofile << setw(30) << m_potential_energy;
  ofile << setw(30) << m_total_energy;
  ofile << setw(30) << m_temperature*epsilon/k_B;
  ofile << setw(30) << m_D << endl;

}

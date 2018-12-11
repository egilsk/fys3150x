#ifndef STATISTICS_SAMPLER_H
#define STATISTICS_SAMPLER_H

#include "system.h"

using namespace std;

class StatisticsSampler {

 private:

  // Declare the physical quantities to sample
  double m_kinetic_energy;
  double m_potential_energy;
  double m_total_energy;
  double m_temperature;
  double m_D;

 public:

  // Constructor
  StatisticsSampler() {}

  // Destructor
  ~StatisticsSampler() {}

  // Samplers
  void sampleKinetic_energy(System system);
  void samplePotential_energy(System system);
  void sampleTotal_energy(System system);
  void sampleTemperature(System system);
  void sampleD(System system, double t);
  void sample(System system, double t);

  // Getters
  double getKinetic_energy() { return m_kinetic_energy; }
  double getPotential_energy() { return m_potential_energy; }
  double getTotal_energy() { return m_total_energy; }
  double getTemperature() { return m_temperature; }
  double getD() { return m_D; }

  // Create header for the output file
  void header_statistics(ofstream& ofile, int n_steps, double temperature_initial, double epsilon, double k_B);
  void header_diffusion(ofstream& ofile, int n_temperatures);

  // Write the sampled results to file
  void output_statistics(ofstream& ofile, double t, double sigma, double epsilon, double u, double k_B);
  void output_diffusion(ofstream& ofile, double T, double epsilon, double k_B);

};

#endif // STATISTICS_SAMPLER_H

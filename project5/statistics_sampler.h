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

  // Create header for the output file
  void header(ofstream& ofile, int n_steps, double temperature_initial, double epsilon, double k_B);

  // Write the sampled results to file
  void output(ofstream& ofile, double t, double sigma, double epsilon, double u, double k_B);

};

#endif // STATISTICS_SAMPLER_H

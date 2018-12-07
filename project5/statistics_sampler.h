#ifndef STATISTICS_SAMPLER_H
#define STATISTICS_SAMPLER_H

#include "system.h"

using namespace std;

class StatisticsSampler {

 private:

  double m_kinetic_energy;
  double m_potential_energy;
  double m_temperature;

 public:

  // Constructor
  StatisticsSampler() {}

  // Destructor
  ~StatisticsSampler() {}

  // Samplers
  void sampleKinetic_energy(System* system);
  void samplePotential_energy(System* system);
  void sampleTemperature(System* system);
  void sample(System* system);

  // Create header for the output file
  void header(ofstream& ofile, int n_steps);

  // Write the sampled results to file
  void output(ofstream& ofile, double t);

};

#endif // STATISTICS_SAMPLER_H

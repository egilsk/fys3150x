#ifndef ISING_H
#define ISING_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <random>
#include <armadillo>
#include "omp.h"

using namespace std;
using namespace arma;

// Initialisation of the lattice
void Initialise(mat&, double&, double&, int);

// Monte Carlo sampling with the Metropolis algorithm
void Metropolis(vec&, mat&, double, int, int, int);

// Create header (expectation values)
void Header_expectation(ofstream&, int, int, int, int);

// Create header (equilibration analysis)
void Header_equilibration(ofstream&, int, int);

// Create header (probability analysis)
void Header_probability(ofstream&, int, int);

// Write to file (expectation values)
void Output_expectation(ofstream&, mat, vec, int);

// Write to file (equilibration values)
void Output_equilibration(ofstream&, mat, int, int, int);

// Write to file (expectation values)
void Output_probability(ofstream&, mat, int, int, int);

// Periodic boundary condition
inline int periodic(int i, int limit, int add) { return (limit + i + add) % (limit); }

#endif // ISING_H

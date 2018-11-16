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

// Create header
void Header(ofstream&, int, int);

// Write to file
void Output(ofstream&, mat, vec, int);

// Periodic boundary condition
inline int periodic(int i, int limit, int add) { return (limit + i + add) % (limit); }

#endif // ISING_H

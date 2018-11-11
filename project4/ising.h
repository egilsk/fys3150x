#ifndef ISING_H
#define ISING_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <random>
#include <armadillo>

using namespace std;
using namespace arma;

// Initialisation of the lattice
void Initialise(mat&, double&, double&, int);

// Monte Carlo sampling with the Metropolis algorithm
void Metropolis(vec&, double, int, int, ofstream&);

// Create header
void Header(ofstream&, int);

// Write to file
void Output(ofstream&, vec, double);

// Periodic boundary condition
inline int periodic(int i, int limit, int add) { return (limit + i + add) % (limit); }

#endif // ISING_H

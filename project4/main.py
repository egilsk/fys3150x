import sys
import numpy as np
import matplotlib.pyplot as plt

# Read the name of the input data file from the command line
if len(sys.argv) <= 1:
    print "Error:", sys.argv[0], "reads the name of the input file"
    exit(1)
else:
    datafile = sys.argv[1]

# Open input data file and read in the results
with open(datafile, 'r') as infile:
    
    # Read number of MC cycles
    n_cycles = int(infile.readline().split()[-1])
    cycles = np.linspace(1, n_cycles, n_cycles)
    
    # Read number of variables
    n_variables = len(infile.readline().split())

    # Create array storing the data
    data = np.zeros((n_cycles,n_variables))

    # Read the data
    for i in range(n_cycles):
        data[i] = infile.readline().split()

# ENERGY

# Create and set up a figure
fig1 = plt.figure()
plt.xlabel("MC cycles")
plt.ylabel("Energy [J]")
#plt.axis([0, n_cycles, -10, 10])
plt.title("Equilibration time for the energy")

# Plot
plt.plot(cycles, data[:,0], 'o', ms=1)

# MAGNETISATION

# Create and set up a figure
fig2 = plt.figure()
plt.xlabel("MC cycles")
plt.ylabel("Magnetisation [# of spins]")
#plt.axis([0, n_cycles, -5, 5])
plt.title("Equilibration time for the magnetisation")

# Plot
plt.plot(cycles, data[:,1], 'o', ms=1)

# ACCEPTED MOVES

# Create and set up a figure
fig3 = plt.figure()
plt.xlabel("MC cycles")
plt.ylabel("Number of accepted moves")
#plt.axis([0, n_cycles, -5, 5])
plt.title("Time development for the number of accepted moves")

# Plot
plt.plot(cycles, data[:,2], 'o', ms=1)

plt.show()

# Save the plot
#plt.savefig(datafile.replace(".dat",".png"))

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
plt.axis([0, n_cycles, -2.0, -1.99])
plt.title("Equilibration of the Energy (T = 1.0, unordered)")

# Plot
plt.plot(cycles, data[:,0], 'o', ms=1)

# Save the plot
#plt.savefig("ising_energy.png")

# MAGNETISATION

# Create and set up a figure
fig2 = plt.figure()
plt.xlabel("MC cycles")
plt.ylabel("Magnetisation [1]")
#plt.axis([0, n_cycles, -5, 5])
plt.title("Equilibration of the Magnetisation (T = 1.0, unordered)")

# Plot
plt.plot(cycles, data[:,1], 'o', ms=1)

# Save the plot
#plt.savefig("ising_magnetisation.png")

# ACCEPTANCE RATIO

# Create and set up a figure
fig3 = plt.figure()
plt.xlabel("MC cycles")
plt.ylabel("Acceptance ratio")
#plt.axis([0, n_cycles, 0, 1])
plt.title("Development of the Acceptance Ratio (T = 1.0, unordered)")

# Plot
plt.plot(cycles, data[:,2], 'o', ms=1)

# Save the plot
#plt.savefig("ising_acceptance.png")

plt.show()

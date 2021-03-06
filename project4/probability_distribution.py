import sys
import numpy as np
import matplotlib.pyplot as plt
import matplotlib as mpl

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

    # Create array storing the energies
    energy = np.zeros(n_cycles)

    infile.readline()

    # Read the data
    for i in range(n_cycles):
        energy[i] = float(infile.readline())

# Create and set up a figure
fig1 = plt.figure()
plt.xlabel("Energy [J]")
plt.ylabel("Probability density")
plt.title("Probability distribution (T = 2.4)")

# Plot
plt.hist(energy) #, bins="auto", density="True")

# Save the plot
#plt.savefig("ising_probability2.png")

plt.show()

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

    # Read number of temperatures
    n_temp = int(infile.readline().split()[-1])

    # Read number of spins
    n_spin = int(infile.readline().split()[-1])

    # Read number of variables
    n_variables = len(infile.readline().split())
    
    # Create array storing the data
    data = np.zeros((n_temp,n_variables))

    # Read the data
    for i in range(n_temp):
        data[i] = infile.readline().split()

# ENERGY

# Create and set up a figure
fig1 = plt.figure()
plt.xlabel("Temperature [kT/J]")
plt.ylabel("Energy [J]")
plt.title("Mean energy as function of temperature")

# Plot
plt.plot(data[:,0], data[:,1])

# Save the plot
plt.savefig("energy60.png")

# MAGNETISATION

# Create and set up a figure
fig2 = plt.figure()
plt.xlabel("Temperature [kT/J]")
plt.ylabel("Magnetisation [1]")
plt.title("Mean magnetisation as function of temperature")

# Plot
plt.plot(data[:,0], data[:,2])

# Save the plot
plt.savefig("magnetisation60.png")

# HEAT CAPACITY

# Create and set up a figure
fig3 = plt.figure()
plt.xlabel("Temperature [kT/J]")
plt.ylabel(r"Heat capacity [J$^2$/kT$^2$]")
plt.title("Heat capacity as function of temperature")

# Plot
plt.plot(data[:,0], data[:,3])

# Save the plot
plt.savefig("heat.png")

# SUSCEPTIBILITY

# Create and set up a figure
fig4 = plt.figure()
plt.xlabel("Temperature [kT/J]")
plt.ylabel("Susceptibility [1/kT]")
plt.title("Susceptibility as function of temperature")

# Plot
plt.plot(data[:,0], data[:,4])

# Save the plot
plt.savefig("susceptibility.png")

plt.show()

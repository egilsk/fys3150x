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

    # Read number of temperatures
    n_temperature = int(infile.readline().split()[-1])

    infile.readline()

    # Create arrays storing the temperatures and diffusion constants
    temperature = np.zeros(n_temperature)
    diffusion_constant = np.zeros(n_temperature)

    # Read the data
    for i in range(n_temperature):
        line = infile.readline().split()
        temperature[i] = float(line[0])
        diffusion_constant[i] = float(line[1])

# Create and set up a figure
fig = plt.figure()
plt.xlabel("Temperature [K]")
plt.ylabel("Diffusion constant " + r"$[\sigma*\sqrt{\epsilon/u}]$")
plt.title("Diffusion Constant as Function of Temperature")

# Plot
plt.plot(temperature, diffusion_constant)

# Save the plot
#plt.savefig("temperature.png")

plt.show()

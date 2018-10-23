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
    theta = np.zeros(415)
    # Read the data
    for i in range(415):
        theta[i] = infile.readline()

#----------------------------------------------------------------------------

# PLOT

# Create a figure, and set it up
fig = plt.figure()
plt.xlabel("Number of orbits")
plt.ylabel("theta_p [\'\']")
plt.title("Mercury Percession")

# Plot the position of the sun and the planets
plt.plot(theta, 'o')

# Save the plot
#plt.savefig(datafile.replace(".dat",".png"))
plt.show()

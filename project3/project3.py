import sys
import numpy as np
import matplotlib.pyplot as plt
import re

# Read the name of the input data file from the command line
if len(sys.argv) <= 1:
    print "Error:", sys.argv[0], "reads the name of the input file (without .dat)"
    exit(1)
else:
    datafile = sys.argv[1]

# Open input data file and read in the results
with open(datafile + ".dat", 'r') as infile:
    # Read the number of points
    n = int(infile.readline().split()[-1])
    # Define an array which stores the data
    data = np.zeros((n,5))
    # Read the data
    infile.readline()
    for i in range(n):
        data[i] = infile.readline().split()
    
# Plot the results
plt.plot(data[:,1], data[:,2], label = datafile.split("_")[-1])
plt.xlabel("x")
plt.ylabel("y")
plt.axis("equal")
plt.legend()
plt.savefig(datafile + ".png")

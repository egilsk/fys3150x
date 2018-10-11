import sys
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
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

# Interactive mode on
plt.ion()

# Set up a figure
fig = plt.figure()
fig.suptitle("Solar system")
ax = fig.add_subplot(111)
ax.grid('on')
ax.set_xlabel("x [AU]")
ax.set_ylabel("y [AU]")
ax.axis("equal")
ax.axis([-2 , 2, -2, 2])

# Plot the inital system
line, = ax.plot(data[0,1], data[0,2], 'o')

plt.draw()

# Animation
for i in range(1,n):
    line.set_xdata(data[i,1])
    line.set_ydata(data[i,2])
    plt.draw()
    plt.pause(0.01)

# Interactive mode off
plt.ioff()



# Plot the results
plt.plot(data[:,1], data[:,2], label = datafile.split("_")[-1])
plt.xlabel("x")
plt.ylabel("y")
plt.axis("equal")
plt.legend()
plt.savefig(datafile + ".png")
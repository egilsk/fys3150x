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

# Create a figure, and set it up
fig = plt.figure()
plt.xlabel("Number of orbits")
plt.ylabel(r"$\theta_p$" + " [arcsec]")
<<<<<<< HEAD:project3/sandbox.py
plt.title("Mercury Percession")
=======
plt.title("Mercury's Perihelion Precession")
>>>>>>> 4c0863f1a1ab2eb7e5ba45ec5b8795a80ea8d34d:project3/mercury_precession.py

# Plot the perihelion precession angle
plt.plot(theta, 'o')

# Save the plot
plt.savefig(datafile.replace(".dat",".png"))
#plt.show()

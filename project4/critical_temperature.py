import sys
import numpy as np
import matplotlib.pyplot as plt

#Read the name of the input data files from the command line
if len(sys.argv) <= 4:
    print "Error:", sys.argv[0], "reads the name of the input files"
    exit(1)

# Define the number of input files
n_files = len(sys.argv) - 1

# Create array storing the critical temperatures
T_C_L = np.zeros(n_files)

# Create array storing the number of spins
L = np.zeros(n_files)

# Loop over the data files
for i in range(n_files):

    # Open input data file and read in the results
    with open(sys.argv[i+1], 'r') as infile:

        # Read number of MC cycles
        infile.readline()

        # Read number of temperatures
        n_temp = int(infile.readline().split()[-1])

        # Read number of spins
        L[i] = int(infile.readline().split()[-1])

        # Read number of variables
        infile.readline()

        # Create variable storing the maximal susceptibility
        max = 0

        # Find the critical temperature
        for j in range(n_temp):
            line = infile.readline().split()
            if line[-1] > max:
                max = line[-1]
                T_C_L[i] = line[0]

# Invert the length
L_inv = L**(-1)

# Least squares polynomial fit
p, V = np.polyfit(L_inv, T_C_L, 1, cov=True)
f = np.polyval(p, L_inv)

print "The critical temperature: {} +/- {}".format(p[1], np.sqrt(V[1][1]))

# Create and set up a figure
fig1 = plt.figure()
plt.xlabel("1/L")
plt.ylabel("T_C")
plt.title("The critical temperature as a function of 1/L")
plt.axis([0, 0.03, 2, 2.5])

# Plot
plt.plot(L_inv,f)
plt.plot(L_inv, T_C_L, "bo")
plt.show()

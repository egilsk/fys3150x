import sys
import numpy as np
import matplotlib.pyplot as plt

#Read the name of the input data files from the command line
if len(sys.argv) <= 4:
    print "Error:", sys.argv[0], "reads the name of the input files"
    exit(1)
    
# Create array storing the critical temperatures
T_C_L = np.zeros(len(sys.argv) - 1)

# Create array storing the number of spins
L = np.zeros(len(sys.argv) - 1)

# Loop over the data files
for i in range(len(sys.argv) - 1):

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
L = L**(-1)

# Least squares polynomial fit
p = np.polyfit(L, T_C_L, 1)
f = np.polyval(p, L)

print "The critical temperature: ", p[1]

# Create and set up a figure
fig1 = plt.figure()
plt.xlabel("1/L")
plt.ylabel("T_C")
plt.title("The critical temperature as a function of 1/L")
plt.axis([0, 0.03, 2, 2.5])

# Plot
plt.plot(L,f)
plt.plot(L, T_C_L, "bo")
plt.show()

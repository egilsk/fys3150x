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

    # Read number of time points
    n_time = int(infile.readline().split()[-1]) + 2

    # Read the initial temperature
    temperature_initial = float(infile.readline().split()[-1])

    infile.readline()

    # Create arrays storing the time and the temperatures
    time = np.zeros(n_time)
    temperature = np.zeros(n_time)

    # Read the data
    for i in range(n_time):
        line = infile.readline().split()
        time[i] = float(line[0])
        temperature[i] = float(line[-2])

print time[-1]

# Create and set up a figure
fig = plt.figure()
plt.xlabel("Time [ps]")
plt.ylabel("Temperature Ratio")
plt.title("Ratio of Temperature to Initial Temperature")

# Plot
plt.plot(time, temperature/temperature_initial)

# Save the plot
#plt.savefig("temperature.png")

plt.show()

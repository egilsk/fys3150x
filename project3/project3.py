import sys
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import re
#import matplotlib
#matplotlib.use("Agg")

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
    data = np.zeros((n,6))
    # Read the data
    infile.readline()
    for i in range(n):
        data[i] = infile.readline().split()

#----------------------------------------------------------------------------

# Plot

fig1 = plt.figure()
plt.plot(data[:,1], data[:,2], label = datafile.split("_")[-1])
plt.plot(0,0,'yo', markersize=12)
plt.xlabel("x")
plt.ylabel("y")
plt.axis("equal")
plt.legend()
plt.savefig(datafile + ".png")
plt.show()

#----------------------------------------------------------------------------
"""
# Animation

# Define animate function
def animate(n, data, line):
    line.set_data(data[..., :n])
    return line,

# Collect x- and y-values
data = np.array((data[:,1], data[:,2]))

# Create figure
fig2 = plt.figure()
plt.axis("equal")
plt.xlim(-2, 2)
plt.ylim(-2, 2)
plt.xlabel('x [AU]')
plt.ylabel('y [AU]')
plt.title('Solar system')

# Initialise the plot
line, = plt.plot([], [], '--')

# Run the animation
ani = animation.FuncAnimation(fig2, animate, n, fargs=(data, line),
                                   interval=50, blit=True)

plt.show()

# Set up formatting for the movie file
Writer = animation.writers['ffmpeg']
writer = Writer(fps=15, metadata=dict(artist='Me'), bitrate=1800)

# Save the animation as mp4 file
ani.save('solar_system.mp4', writer=writer)

"""

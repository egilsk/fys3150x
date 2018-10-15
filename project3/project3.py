import sys
import numpy as np
import matplotlib as mpl
import matplotlib.pyplot as plt
import matplotlib.animation as animation

#-----------------------------------------------------------------------------

# COLLECT DATA

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
    data = np.zeros((n,13))
    # Read the data
    infile.readline()
    infile.readline()
    for i in range(n):
        data[i] = infile.readline().split()

#----------------------------------------------------------------------------

# PLOT

# Create a figure, and set it up
fig1 = plt.figure()
plt.axis("equal")
plt.xlabel("x [AU]")
plt.ylabel("y [AU]")
plt.title(" Solar system ")

# Plot the position of the sun and the planets
plt.plot(data[:,1], data[:,2], label="Earth")
plt.plot(data[:,7], data[:,8], label="Jupiter")
plt.plot(0, 0, 'yo', markersize=12, label="Sun" )
mpl.rcParams['legend.numpoints'] = 1
plt.legend()

# Save the plot
plt.savefig(datafile + ".png")
plt.close()

#----------------------------------------------------------------------------

# ANIMATION

# Create a figure and an axis, and set it up
fig2 = plt.figure()
ax = plt.axes(aspect="equal", xlim=(-10, 10), ylim=(-10, 10),
                title="Solar System", xlabel="x [AU]", ylabel="y [AU]")
ax.grid()
mpl.rcParams['legend.numpoints'] = 1

# Initialize the orbits and the timing
sun, = ax.plot(0,0, "yo", ms=12, label="Sun")
earth_orbit, = ax.plot([], [], "--", lw=1)
earth, = ax.plot([], [], "bo", ms=4, label="Earth")
jupiter_orbit, = ax.plot([], [], "--", lw=1)
jupiter, = ax.plot([], [], "ro", ms=8, label="Jupiter")

time_text = ax.text(0.05, 0.95, "", transform=ax.transAxes)

# Define the init-function, which draws a clear frame
def init():
    earth_orbit.set_data([], [])
    earth.set_data([], [])
    jupiter_orbit.set_data([], [])
    jupiter.set_data([], [])
    time_text.set_text("")
    return earth_orbit, earth, jupiter_orbit, jupiter, time_text

# Define the animate-function, which is called at each frame
def animate(i):
    earth_orbit.set_data(data[:i,1], data[:i,2])
    earth.set_data(data[i,1], data[i,2])
    jupiter_orbit.set_data(data[:i,7], data[:i,8])
    jupiter.set_data(data[i,7], data[i,8])
    time_text.set_text("%.1f years" % data[i,0])
    ax.legend()
    return earth_orbit, earth, jupiter_orbit, jupiter, time_text

# Run the animation
ani = animation.FuncAnimation(fig2, animate, frames=len(data[:,0]),
                                init_func=init, interval=10, blit=True)
plt.show()

# Save the animation
#ani.save('earth.mp4')

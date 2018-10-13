import sys
import numpy as np
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
    data = np.zeros((n,5))
    # Read the data
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
plt.title(" Solar system (" + datafile.split("_")[-1] + ")")

# Plot the position of the sun and the planets
plt.plot(data[:,1], data[:,2], label="Earth")
plt.plot(0, 0, 'yo', markersize=12, label="Sun" )
plt.legend()

# Save the plot
plt.savefig(datafile + ".png")
plt.close()

#----------------------------------------------------------------------------

# ANIMATION

# Create a figure and an axis, and set it up
fig2 = plt.figure()
ax = plt.axes(aspect="equal", xlim=(-2, 2), ylim=(-2, 2),
                title="Solar System", xlabel="x [AU]", ylabel="y [AU]")
ax.grid()

# Initialize the orbits and the timing
sun, = ax.plot(0,0, "yo", ms=12)
orbit, = ax.plot([], [], "--", lw=1)
planet, = ax.plot([], [], "o", ms=2)
time_text = ax.text(0.05, 0.9, "", transform=ax.transAxes)

# Define the init-function, which draws a clear frame
def init():
    orbit.set_data([], [])
    planet.set_data([], [])
    time_text.set_text("")
    return orbit, planet, time_text

# Define the animate-function, which is called at each frame
def animate(i):
    orbit.set_data(data[:i,1], data[:i,2])
    planet.set_data(data[i,1], data[i,2])
    time_text.set_text("%.1f years" % data[i,0])
    return orbit, planet, time_text

# Run the animation
ani = animation.FuncAnimation(fig2, animate, frames=len(data[:,0]),
                                init_func=init, interval=25, blit=True)
plt.show()

# Save the animation
#ani.save('earth.mp4')

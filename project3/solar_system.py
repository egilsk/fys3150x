import sys
import numpy as np
import matplotlib as mpl
import matplotlib.pyplot as plt
import matplotlib.animation as animation

#-----------------------------------------------------------------------------

# COLLECT DATA

# Read the name of the input data file from the command line
if len(sys.argv) <= 1:
    print "Error:", sys.argv[0], "reads the name of the input file"
    exit(1)
else:
    datafile = sys.argv[1]

# Open input data file and read in the results
with open(datafile, 'r') as infile:
    # Read the number of points
    n_points = int(infile.readline().split()[-1])
    # Read the names of the bodies
    names = infile.readline().replace(":","").split()
    # Read the number of columns
    n_columns = len(infile.readline().split())
    # Define an array which stores the data
    data = np.zeros((n_points,n_columns))
    # Read the data
    for i in range(n_points):
        data[i] = infile.readline().split()

#----------------------------------------------------------------------------

# PLOT

# Create a figure, and set it up
fig1 = plt.figure()
plt.xlabel("x [AU]")
plt.ylabel("y [AU]")
plt.title("Inner Solar System")
plt.axis("equal")
#plt.axis([-2, 2, -2, 2])
plt.grid()

# Plot the position of the sun and the planets
j = 1
for i in range(len(names)):
    plt.plot(data[:,j], data[:,j+1], label=names[i])
    j += 3

# Set up the legend
mpl.rcParams["legend.numpoints"] = 1
plt.legend(loc="best", fontsize="xx-small")

# Save the plot
plt.savefig(datafile.replace(".dat",".png"))
plt.show()

#----------------------------------------------------------------------------
"""
# ANIMATION

# Create a figure and an axis, and set it up
fig2 = plt.figure()
ax = plt.axes(aspect="equal", xlim=(-50, 50), ylim=(-50, 50),
                title="Solar System", xlabel="x [AU]", ylabel="y [AU]")
ax.grid()
mpl.rcParams["legend.numpoints"] = 1

# Specify color and size
color = ["yo", "ko", "yo", "bo", "ro", "ro", "yo", "bo", "bo", "ko"]
size = [4, 1, 1, 1, 1, 2, 2, 2, 2, 1]

# Initialise the orbits and the timing
orbits = []
planets = []
j = 0
for name in names:
    orbit, = ax.plot([], [], "-", lw=1, label=name)
    orbits.append(orbit)
    planet, = ax.plot([], [], color[j], ms=size[j])
    planets.append(planet)
    j += 1

time_text = ax.text(0.05, 0.95, "", transform=ax.transAxes)

# Define the init-function, which draws a clear frame
def init():
    for j in range(len(names)):
        orbits[j].set_data([], [])
        planets[j].set_data([], [])
    time_text.set_text("")
    return tuple(orbits) + tuple(planets) + (time_text,)

# Define the animate-function, which is called at each frame
def animate(i):
    k = 1
    for j in range(len(names)):
        orbits[j].set_data(data[:i,k], data[:i,k+1])
        planets[j].set_data(data[i,k], data[i,k+1])
        k += 3
    time_text.set_text("%.1f years" % data[i,0])
    ax.legend(loc="best", fontsize="xx-small")
    return tuple(orbits) + tuple(planets) + (time_text,)

# Run the animation
ani = animation.FuncAnimation(fig2, animate, frames=len(data[:,0]),
                                init_func=init, interval=1, blit=True)

plt.show()

# Save the animation
<<<<<<< HEAD
#ani.save(datafile.replace(".dat",".mp4"))
=======
ani.save(datafile.replace(".txt",".mp4"))
>>>>>>> b6af757ae23031f1b620b83ad4aa008f624aa459
"""

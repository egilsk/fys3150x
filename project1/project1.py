import sys
import numpy as np
import matplotlib.pyplot as plt

N = int(sys.argv[1])
h = np.zeros(N)
max_error = np.zeros(N)

for I in range(1, N+1):
    n = 10**I + 2
    x = np.zeros((n,4))
    datafile = "data{}.dat".format(I)
    with open(datafile, 'r') as infile:
        infile.readline()
        for i in range(n):
            x[i] = infile.readline().split()
        infile.readline()
        h[I-1] = infile.readline()
    max_error[I-1] = max(x[1:-1,3])
    plt.figure(I)
    plt.plot(x[:,0],x[:,1],x[:,0],x[:,2])
    plt.savefig("plot{}.png".format(I))

plt.figure(N+1)
plt.plot(h,max_error)
plt.savefig("plot_error.png")

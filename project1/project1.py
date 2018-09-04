import sys
import numpy as np
import matplotlib.pyplot as plt

N = int(sys.argv[1])

for I in range(1, N+1):
    n = 10**I + 2
    x = np.zeros((n,3))
    datafile = "data{}.dat".format(I)
    with open(datafile, 'r') as infile:
        infile.readline()
        for i in range(n):
            x[i] = infile.readline().split()
    plt.figure(I)
    plt.plot(x[:,0],x[:,1],x[:,0],x[:,2])
    plt.savefig("plot{}.png".format(I))

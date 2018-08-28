import sys
import numpy as np
import matplotlib.pyplot as plt

option = int(sys.argv[1])

max = 6
N = np.zeros(max, dtype="int")
for i in xrange(max):
    N[i] = 10**(i+1)

i_err = 0
error = np.zeros(max)

if option == 32:
    for n in N:
        s_up = np.float32(0)
        for i in xrange(1,n+1):
            s_up += np.float32(1./i)

        s_down = np.float32(0)
        for i in xrange(n,0,-1):
            s_down += np.float32(1./i)

        error[i_err] = abs((s_up - s_down)/s_down)
        i_err += 1
elif option == 64:
    for n in N:
        s_up = np.float64(0)
        for i in xrange(1,n+1):
            s_up += np.float64(1./i)

        s_down = np.float64(0)
        for i in xrange(n,0,-1):
            s_down += np.float64(1./i)

        error[i_err] = abs((s_up - s_down)/s_down)
        i_err += 1
else:
    sys.exit("Choose 32 or 64")

x = np.log10(N[1:])
y = np.log10(error[1:])
plt.plot(x,y)
plt.show()

import sys
import numpy as np
import matplotlib.pyplot as plt

# Bestemmer 32- eller 64-bit
option = int(sys.argv[1])

# Array med N-er
num_N = int(sys.argv[2])
N = np.zeros(num_N, dtype="int")
for i in xrange(num_N):
    N[i] = 10**(i+1)

# Initierer utregning av feilen
i_err = 0
error = np.zeros(num_N)

# Utforer summasjonen for 32- eller 64-bit
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

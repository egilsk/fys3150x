import scipy.sparse as sparse

import matplotlib.pyplot as plt

import numpy as np
from numpy import exp, pi

# Den initielle bolgefunksjonen
def Psi_0(x):
    x0 = 5.0    # [fm]
    a = 1.0     # [fm]
    k = 1.38    # [fm^-1]

    A = (1/(2*pi*a**2))**0.25
    f = exp(-(x-x0)**2/(4*a**2))
    g = exp(1j*k*x)

    return A*f*g

# Boks-potensialet
def Potensial_1(x):
    V0 = 34         # [MeV]
    R = 7.3         # [fm]
    delta_x = 17    # [fm]
    x_slutt = x[-1] # [fm]

    potensial = np.zeros(len(x))

    #Plassering av boksen
    dx = delta_x/x_slutt
    x0 = R/x_slutt
    potensial[x0*len(x) : (x0+dx)*len(x)] = V0

    return potensial

# Elektrostatisk potensial
def Potensial_2(x):
    z_alpha = 2     # [e]
    z_radon = 86    # [e]
    ke = 1.44       # [MeV fm]
    R = 7.3         # [fm]
    x_slutt = x[-1] # [fm]

    potensial = np.zeros(len(x))

    V = z_alpha*z_radon*ke
    x0 = R/x_slutt

    potensial[x0*len(x):] = V / x[x0*len(x):]

    return potensial

# Rom
nx = 10001
x_slutt = 200.0 # [fm]
dx = x_slutt/nx # [fm]

x = np.linspace(0, x_slutt, nx)

# Tid
T = 0.2     # [as]
dt = 1.0e-5 # [as]

# Konstanter
hbar_c = 197.3  # [Mev fm]
c = 3.0e5       # [fm / as]
E0 = 3727.0     # [MeV]

c1 = (1j*hbar_c*c) / (2*E0)
c2 = -(1j*c) / hbar_c

# Lager identitetsmatrisen
I = sparse.identity(nx)

# Lager D-matrisen
data = np.ones((3, nx))
data[1] = -2*data[1]
diags = [-1,0,1]
D = c1/dx**2 * sparse.spdiags(data, diags, nx, nx)

# Lager V-matrisen
V_data = Potensial_1(x)                                  # Velge potensial
V_diags = [0]
V = c2 * sparse.spdiags(V_data, V_diags, nx, nx)

# Interactive mode on
plt.ion()

# Setter opp en figur
fig = plt.figure()
fig.suptitle("Tidsutviklingen av bolgefunksjonen")
ax = fig.add_subplot(111)
ax.grid('on')
ax.set_xlabel("x [fm]")
ax.set_ylabel("$|\Psi(x,t)|^2$ [1/fm] og V(x) [MeV]")
ax.set_xlim(0,x_slutt)
#ax.set_ylim(0,0.01)                                      # Justere y-aksen
ax.legend(loc='best')

# Plotter den initielle bolgefunksjonen
line, = ax.plot(x, abs(Psi_0(x))**2, label='$|\Psi(x,t)|^2$')

# Plotter potensialet
ax.plot(x, V_data/1000, label='$V(x)$')

ax.legend()
plt.draw()

Psi = Psi_0(x)
t = 0       # [as]

# Crank-Nicolsons metode
while t < T:
    A = (I - dt/2*(D + V))
    b = (I + dt/2*(D + V)) * Psi

    Psi = sparse.linalg.spsolve(A, b)

    t += dt

    # Animasjon
    line.set_ydata(abs(Psi)**2)
    plt.draw()
    plt.pause(0.001)

# Interactive mode off
plt.ioff()

import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import scipy.io

samples = np.load("probe_readings.npy")
sample_rate = 2e6

# Extract I and Q components from the complex samples
I = np.real(samples)  # In-phase component (real part)
Q = np.imag(samples)  # Quadrature component (imaginary part)

# Create a time vector (or sample indices)
time = np.arange(len(samples))/sample_rate

# Create a 3D plot
fig = plt.figure(figsize=(10, 6))
ax = fig.add_subplot(111, projection='3d')

# Plot I, Q, and time (or sample index) in 3D
ax.scatter(I, Q, time, s=1, color='blue', alpha=0.5)

# Labels and title
ax.set_xlabel('In-Phase (I)')
ax.set_ylabel('Quadrature (Q)')
ax.set_zlabel('Time (samples)')
ax.set_title('3D IQ Plot')

# Warning: THIS PLOT WILL TAKE A WHILE ITS A BUNCH OF POINTS
plt.show()

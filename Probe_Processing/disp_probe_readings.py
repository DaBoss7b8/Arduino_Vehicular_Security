# This code simply displays the readings collected from the probe, which is stored in a npy file

import scipy.io
import matplotlib.pyplot as plt
import numpy as np

samples = np.load("probe_readings.npy")


plt.plot(samples)
plt.show()
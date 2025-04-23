# This code actually runs the SDR code, and then saves the sample to a npy file

import numpy as np
import matplotlib.pyplot as plt
from rtlsdr import RtlSdr
from scipy.signal import find_peaks

# Configure the SDR
sdr = RtlSdr()
sdr.sample_rate = 2e6  # 2.048 MS/s
sdr.center_freq = 125e6  # 125 MHz upconverter + 500 kHz
sdr.gain = 'auto'

# Read samples
num_samples = 1024 * 1024
samples = sdr.read_samples(num_samples)

# Close the SDR
sdr.close()


np.save("probe_readings.npy", samples)



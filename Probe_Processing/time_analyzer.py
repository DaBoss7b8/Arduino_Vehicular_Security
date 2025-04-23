import numpy as np
import matplotlib.pyplot as plt
from rtlsdr import RtlSdr

# Configure the SDR
sdr = RtlSdr()
sdr.sample_rate = 2e6  # 2 M/s
sdr.center_freq = 125.5e6  # 125 MHz upconverter + 500 kHz
sdr.gain = 4

# Read samples
num_samples = 1024 * 16
samples = sdr.read_samples(num_samples)

# Close the SDR
sdr.close()

# Plot the samples on a time scale
time = np.arange(0, num_samples) / sdr.sample_rate
plt.plot(time, np.real(samples), label='Real')
#plt.plot(time, np.imag(samples), label='Imaginary')
plt.xlabel('Time (s)')
plt.ylabel('Amplitude')
plt.title('SDR Samples at 500 kHz with 125 MHz Upconverter')
plt.legend()
plt.show()
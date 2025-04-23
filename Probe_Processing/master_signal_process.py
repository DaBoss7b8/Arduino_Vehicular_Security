import numpy as np
import matplotlib.pyplot as plt
from scipy.signal import find_peaks
import scipy.io
from scipy.signal import find_peaks

samples = np.load("probe_readings.npy")
sample_rate = 2e6
num_samples = 1024 * 1024


# Plot the collected samples, no extra gimicks
t = np.arange(num_samples) / sample_rate
plt.figure(figsize=(12, 6))
plt.plot(t, np.abs(samples), label='Absolute Value')
plt.xlabel('Time (s)')
plt.ylabel('Amplitude')
plt.title('SDR Samples at 500 kHz with 125 MHz Upconverter')
plt.legend()
plt.show()

# Plotting the Absolute Value of the FFT of the samples
plt.plot(np.abs(np.fft.fft(samples)), label='Absolute Value')
plt.xlabel('Frequency')
plt.ylabel('Amplitude')
plt.title('Frequency Spectrum of SDR Samples')
plt.legend()
plt.show()

# The previous plot had a HUGE spike at DC, which kind of makes readings quite redundant
# This can be fixed by basically making the readings at DC be zero, which is an easy way of applying a filter LOL

filteredfft = np.fft.fft(samples)
filter_length = 1024*8
filter = [0]*filter_length
filteredfft[:filter_length] = filter
filteredfft[-filter_length:] = filter

plt.plot(np.abs(filteredfft))
plt.xlabel('Frequency')
plt.ylabel('Amplitude')
plt.title('Frequency Spectrum of SDR Samples - DC Spike Filtered')
plt.legend()
plt.show()

# Since the DC Spike has been removed, the inverse FFT of the filtered dataset can be taken, and that presents us with clean values

data = np.fft.ifft(filteredfft)                                 # NOTE: The "data" variable is the raw samples, with the DC spike samples removed
plt.plot(t, np.abs(data), label='Real')
plt.xlabel('Time (s)')
plt.ylabel('Amplitude')
plt.title('SDR Samples - DC Spike Removed')
plt.legend()
plt.show()



absdata = np.abs(data)
smoothening = np.array([1,1,1,1])
result = np.convolve(absdata.T, smoothening.T, mode = "same")
plt.plot(t, result, label='Real')
plt.xlabel('Time (s)')
plt.ylabel('Amplitude')
plt.title('Filtered Data with a 4-Point Moving Average')
plt.legend()
plt.show()



# Find peaks
peaks, _ = find_peaks(result, height=2)  # 'height' is a threshold to ignore noise

# Choose the first peak (or any other)
peak_idx = peaks[0]

# Define a window around the peak — tune this as needed
pre = 50  # samples before the peak
post = 500  # samples after the peak

start_idx = max(0, peak_idx - pre)
end_idx = min(len(result), peak_idx + post)

# Plot zoomed-in segment
plt.plot(t[start_idx:end_idx], result[start_idx:end_idx])
plt.title("Zoomed-In Peak")
plt.xlabel("Time (s)")
plt.ylabel("Amplitude")
plt.grid(True)
plt.show()

mat = scipy.io.loadmat('../Oscilloscope_Processing/osc_data.mat')
#print(mat)

time = mat["time"]
data = mat["data"]
sample_rate = 1/mat["sampleInterval"][0]
print(sample_rate)
#print(data)

plt.plot(time, data)
plt.title("Oscilloscope Data")
plt.xlabel("Time (s)")
plt.ylabel("Amplitude")
plt.show()


# Trying to plot both signals on one graph

time_offset = time + 0.0387966

plt.plot(t[start_idx:end_idx], result[start_idx:end_idx], label="Probe Data", color='Blue')
plt.plot(time_offset, data, label="Oscilloscope Data", color='Orange')
plt.legend(loc='upper right', fontsize=10, frameon=True)
plt.title("Graph of Both Probe and Oscilloscope Waveform")
plt.xlabel("Time(s)")
plt.ylabel("Amplitude")
plt.grid(True)
plt.show()








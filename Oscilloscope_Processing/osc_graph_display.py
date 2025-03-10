import scipy.io
import matplotlib.pyplot as plt
mat = scipy.io.loadmat('osc_data.mat')
#print(mat)

time = mat["time"]
data = mat["data"]
sample_rate = 1/mat["sampleInterval"][0]
print(sample_rate)
#print(data)

plt.plot(data)
plt.show()








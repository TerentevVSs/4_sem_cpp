import matplotlib.pyplot as plt
import numpy as np

with open("data.txt") as f:
    data = f.read().splitlines()
threads = np.arange(1, 101)
data = np.array(list(map(lambda x: int(x), data)))
plt.plot(threads, data)
plt.xlabel("Threads")
plt.ylabel("Time, microseconds per number")
plt.show()

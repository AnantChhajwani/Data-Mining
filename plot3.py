import matplotlib.pyplot as plt
import numpy as np

file3 = open("optics.txt", "r")
values = []
for line in file3:
	values.append(float(line))

plt.bar([i for i in range(len(values))], values)
plt.show()
import numpy as np
from matplotlib import pyplot as plt
import itertools

file1 = open("points5.txt","r")
inp = []
for line in file1:
	lis = []
	for coord in line.split():
		lis.append(float(coord))
	inp.append(lis)

file2 = open("dbscan.txt", "r")
clusters = []
lis = []
cnt = 0
for line in file2:
	if line[0] == '#':
		if (cnt != 0):
			clusters.append(lis)
		lis = []
		cnt += 1
	else:
		idx = int(line)
		lis.append(inp[idx])
if len(lis) > 0:
	clusters.append(lis)

for i in clusters:
	print(len(i))


inp = np.array(inp)
x, y = inp.T
plt.scatter(x, y)
plt.show()

#cluster = np.array(clusters)
cnt = 0
colors = ["red", "blue", "green", "pink", "yellow", "purple", "orange", "magenta", "brown", "gold", "silver", ""]
for arr in clusters:
	cnt += 1
	#print (arr)
	arr1 = np.array(arr)
	x, y = arr1.T
	plt.scatter(x, y, color=colors[cnt-1])
plt.show()

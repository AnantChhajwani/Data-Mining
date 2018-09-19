import numpy as np
from matplotlib import pyplot as plt
import itertools

file1 = open("points.txt","r")
inp = []
cnt = 0
for line in file1:
	lis = []
	cnt += 1
	for coord in line.split():
		lis.append(float(coord))
	if cnt < 5:
		print (cnt, lis)
	inp.append(lis)

file2 = open("kmeans.txt", "r")
clusters = []
lis = []
cnt = 0
for line in file2:
	if line[0] == '#':
		#print (line)
		if (cnt != 0):
			clusters.append(lis)
		lis = []
		cnt += 1
	else:
		idx = int(line)
		lis.append(inp[idx])
clusters.append(lis)

print (len(clusters[0]))
print (len(clusters[1]))
print (len(clusters[2]))
print (len(clusters[3]))
print (len(clusters[4]))
print (len(clusters[5]))
print (len(clusters[6]))


inp = np.array(inp)
x, y = inp.T
plt.scatter(x, y)
plt.show()

#cluster = np.array(clusters)
cnt = 0
colors = ["red", "blue", "green", "yellow", "purple", "black", "orange"]
for arr in clusters:
	cnt += 1
	#print (arr)
	arr1 = np.array(arr)
	x, y = arr1.T
	plt.scatter(x, y, color=colors[cnt-1])
plt.show()
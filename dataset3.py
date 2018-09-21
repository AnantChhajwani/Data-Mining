from sklearn.datasets import make_blobs
from sklearn.datasets import make_moons
from sklearn.datasets import make_circles
from matplotlib import pyplot
from pandas import DataFrame
import numpy as np
import random

xt = np.random.uniform(low=0, high=0.5, size=1000)
xs = np.random.uniform(low=-0.5, high=0, size=300)

yt = np.random.uniform(low=0, high=0.5, size=300)
ys = np.random.uniform(low=-0.5, high=0, size=1000)

xt.tolist()
xs.tolist()
yt.tolist()
ys.tolist()

xk = []
yk = []
for i in xt:
	xk.append(i)
for i in xs:
	xk.append(i)
for i in yt:
	yk.append(i)
for i in ys:
	yk.append(i)

random.shuffle(xk)
random.shuffle(yk)

SQRT_2 = 1.41421356237

X3 = []
y3 = []
for i in range(len(xk)):
	X3.append([(xk[i] - yk[i])/SQRT_2, (xk[i] + yk[i])/SQRT_2])
	y3.append(0)

xt = np.random.uniform(low=0, high=0.5, size=1000)
xs = np.random.uniform(low=-0.5, high=0, size=300)

yt = np.random.uniform(low=0, high=0.5, size=300)
ys = np.random.uniform(low=-0.5, high=0, size=1000)

xt.tolist()
xs.tolist()
yt.tolist()
ys.tolist()

xk = []
yk = []
for i in xt:
	xk.append(i)
for i in xs:
	xk.append(i)
for i in yt:
	yk.append(i)
for i in ys:
	yk.append(i)

random.shuffle(xk)
random.shuffle(yk)

SQRT_2 = 1.41421356237

for i in range(len(xk)):
	X3.append([-(xk[i] - yk[i])/SQRT_2 + 1.4, (xk[i] + yk[i])/SQRT_2])
	y3.append(0)

xt = np.random.uniform(low=-3, high=4, size=50)
yt = np.random.uniform(low=-3, high=3, size=50)
random.shuffle(xt)
random.shuffle(yt)

X1, y1 = make_moons(n_samples=1000, noise=0.05)
X2, y2 = make_circles(n_samples=2000, noise=0.05, factor=0.5)

X = []
y = []

X1.tolist()
y1.tolist()
X2.tolist()
y2.tolist()

for i in range(len(X1)):
	y1[i] += 2
	X1[i][0] += 1.4
	X1[i][1] += 1.4

for i in range(len(X1)):
	X.append(X1[i])
	y.append(y1[i])

for i in range(len(X2)):
	X.append(X2[i])
	y.append(y2[i])

for i in range(len(X3)):
	X.append([X3[i][0] - 1.5, X3[i][1] - 2])
	y.append(y3[i] + 4)

for i in range(len(xt)):
	X.append([xt[i], yt[i]])
	y.append(5)

for i in range(len(X)):
	X[i][0] *= 2
	X[i][1] *= 2 

X = np.array(X)
y = np.array(y)

# scatter plot, dots colored by class value
df = DataFrame(dict(x=X[:,0], y=X[:,1], label=y))
colors = {0:'red', 1:'blue', 2:'green', 3:'yellow', 4:'purple', 5:'orange', 6:'pink'}
fig, ax = pyplot.subplots()
grouped = df.groupby('label')
for key, group in grouped:
    group.plot(ax=ax, kind='scatter', x='x', y='y', label=key, color=colors[key])
pyplot.show()

f = open("points5.txt", "w")
for i in X:
	f.write(str(i[0]) + " " + str(i[1]) + "\n")

from sklearn.datasets import make_circles
import matplotlib.pyplot as plt

circles_data, circles_labels = make_circles(n_samples=4000,
                                      noise=.06,
                                      factor=.5)

plt.scatter(circles_data[:,0],
            circles_data[:,1], 
            c = circles_labels,
            cmap='viridis');
plt.show()

f = open("points4.txt", "w")
for i in circles_data:
	f.write(str(i[0]) + " " + str(i[1]) + "\n")
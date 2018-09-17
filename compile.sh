#!/bin/bash

# Clone the repo
git clone https://github.com/AnantChhajwani/Data-Mining.git

# Execute the code
g++ -std=c++11 -O3 kmeans.cpp -o kmeans
g++ -std=c++11 -O3 dbscan.cpp -o dbscan
g++ -std=c++11 -O3 optics.cpp -o optics


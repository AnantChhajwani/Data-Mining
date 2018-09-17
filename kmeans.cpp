#include <bits/stdc++.h>

using namespace std;

// Used for termination condition
// Terminate when number of clusters changed < espilon% of points
const double epsilon = 0.001;

/***
	k : k-means parameter
	d : dimension of dataset
	n : number of points
***/
int k, d, n;

vector< vector <double> > points;
vector <int> clusterIds;
vector <int> numElementsInCluster;
vector< vector <double> > kMeans;

void writeOutput(string fileName) {

	vector <vector <int> > finalAssignments;
	finalAssignments.resize(k);

	for(int i = 0; i < n; i++) {
		finalAssignments[clusterIds[i]].push_back(i);
	}
 
	ofstream outfile (fileName);
	for(int i = 0; i < k; i++) {
		outfile << "#" << i << endl;
		for(int j = 0; j < finalAssignments[i].size(); j++) {
			outfile << finalAssignments[i][j] << endl;
		}
	}	

	outfile.close();
}

void readInput(string fileName) {
	
	ifstream infile (fileName);
	string line;
	n = 0;

	while(getline(infile, line)) {
		stringstream stream(line);
		n++;
		vector <double> currPoint;
		while(true) {
			double n;
			stream >> n;
			if(!stream) break;
			currPoint.push_back(n);
		}
		points.push_back(currPoint);
	}
	infile.close();

	// Initialize dimension
	d = points[0].size();
}

void initialize() {

	// Assign one point to each cluster
	for(int i=0; i < k; i++) {
		clusterIds.push_back(i);
	}

	// Assign random cluster to rest of the points
	srand (time(NULL));
	for(int i = k; i < points.size(); i++) {
		clusterIds.push_back(rand() % k);
	}

	// Initialize kMeans
	kMeans.resize(k);
	for(int i = 0; i < k; i++) {
		kMeans[i].resize(d);
	}

	numElementsInCluster.resize(k);

}

void computeMeans() {

	// Initialize k-means to 0
	for(int i = 0; i < k; i++) {
		numElementsInCluster[i] = 0;
		for(int j = 0; j < d; j++) {
			kMeans[i][j]  = 0;
		}
	}

	for(int i = 0; i < n; i++) {
		int currId = clusterIds[i];
		numElementsInCluster[currId] ++;
		for(int j = 0; j < d; j++) {
			kMeans[currId][j] += points[i][j];
		}
	}

	for(int i = 0; i < k; i++) {
		for(int j = 0; j < d; j++) {
			kMeans[i][j] /= numElementsInCluster[i];
		}
	}
}

void distance(vector<double> p1, vector<double> p2) {
	
	double dist = 0;
	
	for(int i = 0; i < p1.size(); i++) {
		dist += (p1[i] - p2[i]) * (p1[i] - p2[i]);
	}
	
	return dist;
}

bool computeClusterAssignment() {

	int changedClusters = 0;
	for(int i = 0; i < n; i++) {
		
		double minDist = distance(points[i], kMeans[0]);
		int currCluster = 0;
		
		for(int j = 1; j < k; j++) {
			double currDist = distance(points[i], kMeans[j]);
			
			if(currDist < minDist) {
				minDist = currDist;
				currCluster = j;
			}
		}

		if(clusterIds[i] != currCluster) {
			changedClusters++;
		}

		clusterIds[i] = currCluster;
	}

	return changedClusters > (n * epsilon);

}

int main(int argc, char* argv[]) {

	k = atoi(argv[1]);
	string inputFile = argv[2];
	
	// Read input file
	readInput(inputFile);

	// Error handling
	if(points.size() < k) {
		cout<<"Number of points less than number of clusters!\n";
		return 0;
	}

	// Initialize cluster assignment
	initialize();

	// Compute initial means
	computeMeans();

	// Iterate k-means algo till convergence
	while(computeClusterAssignment()) {
		computeMeans();
	}

	// Write output
	writeOutput("kmeans.txt");

	return 0;
}
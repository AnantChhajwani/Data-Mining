#include <bits/stdc++.h>

using namespace std;

// Used for termination condition
// Terminate when number of clusters changed < espilon% of points
const double epsilon = 0.00001;

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

vector <int> bestClusterIds;
double best_value;
bool initupdate = false;

void writeOutput(string fileName) {

	vector <vector <int> > finalAssignments;
	finalAssignments.resize(k);

	for(int i = 0; i < n; i++) {
		finalAssignments[bestClusterIds[i]].push_back(i);
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
			double pt;
			stream >> pt;
			if(!stream) break;
			currPoint.push_back(pt);
		}
		points.push_back(currPoint);
	}
	infile.close();

	// Initialize dimension
	d = points[0].size();
}

double distance(vector<double> p1, vector<double> p2) {
	
	double dist = 0;
	
	for(int i = 0; i < p1.size(); i++) {
		dist += (p1[i] - p2[i]) * (p1[i] - p2[i]);
	}
	
	return dist;
}

void update() {
	if(!initupdate) {
		initupdate = true;
		bestClusterIds.resize(n);
		for(int i = 0; i < clusterIds.size(); i++)
			bestClusterIds[i] = clusterIds[i];
		best_value = 0;
		for(int i = 0; i < n; i++) {
			double dist = distance(points[i], kMeans[bestClusterIds[i]]);
			best_value += dist;
		}
		return;
	}
	int curr_value = 0;
	for(int i = 0; i < n; i++) {
		double dist = distance(points[i], kMeans[bestClusterIds[i]]);
		curr_value += dist;
	}
	if(curr_value > best_value) return;
	for(int i = 0; i < n; i++)
		bestClusterIds[i] = clusterIds[i];
}

void initialize() {
	/*

	// Assign one point to each cluster
	for(int i=0; i < k; i++) {
		clusterIds.push_back(i);
	}

	// Assign random cluster to rest of the points
	srand (time(NULL));
	for(int i = k; i < points.size(); i++) {
		clusterIds.push_back(rand() % k);
	}

	//for(int i = 0; i < points.size(); i++)
	//	cout << clusterIds[i] << " ";

	// Initialize kMeans
	kMeans.resize(k);
	for(int i = 0; i < k; i++) {
		kMeans[i].resize(d);
	}

	numElementsInCluster.resize(k);

	*/

	numElementsInCluster.resize(k);
	clusterIds.resize(n);
	kMeans.resize(k);
	for(int i = 0; i < k; i++)
		kMeans[i].resize(d);

	srand(time(NULL));
	vector <int> vec;
	for(int i = 0; i < k; i++) {
		while(true) {
			int chose = rand() % n;
			bool flag = false;
			for(int j = 0; j < vec.size(); j++) {
				if(vec[j] == chose) flag = true;
			}
			if(!flag) {
				vec.push_back(chose);
				break;
			}
		}
	}

	for(int i = 0; i < k; i++) {
		for(int j = 0; j < d; j++) {
			kMeans[i][j] = points[vec[i]][j];
		}
	}
	numElementsInCluster[0] = n;
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

	int iter = 0;
	while(iter < 10) {
		cout << iter << endl;
		initialize();
		//cout << "hello" << endl;
		int cnt =0;
		while(cnt < 25) {
			cnt++;
			computeClusterAssignment();
		//	cout << "Hi" << endl;
			computeMeans();
		}
		update();
		iter++;
	}

	/*

	// Initialize cluster assignment
	initialize();

	// Compute initial means
	computeMeans();

	// Iterate k-means algo till convergence
	int iter = 0;
	while(iter < 200) {
		iter++;
		computeClusterAssignment();
		computeMeans();
	}

	for(int i = 0; i < k; i++)
		cout << numElementsInCluster[i] << endl;

	*/

	// Write output
	writeOutput("kmeans.txt");

	return 0;
}
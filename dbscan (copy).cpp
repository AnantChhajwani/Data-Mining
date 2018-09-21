#include <bits/stdc++.h>

using namespace std;

int minPts;
double epsilon;

int d, n;
vector< vector <double> > points;
vector <int> label;

void readInput(string fileName) {
	
	ifstream infile (fileName);
	string line;

	while(getline(infile, line)) {
		stringstream stream(line);
		vector <double> currPoint;
		while(true) {
			double pt;
			stream >> pt;
			if(!stream) break;
			currPoint.push_back(pt);
		}
		if(currPoint.size() > 0)
			points.push_back(currPoint);
	}
	infile.close();

	n = points.size();
	d = points[0].size();
}

double distance(vector<double> p1, vector<double> p2) {
	
	double dist = 0;
	
	for(int i = 0; i < p1.size(); i++) {
		dist += (p1[i] - p2[i]) * (p1[i] - p2[i]);
	}
	
	return dist;
}

vector <int> rangeQuery(int idx) {
	vector <int> neighbors;
	for(int i = 0; i < n; i++) {
		if(distance(points[idx], points[i]) < epsilon * epsilon)
			neighbors.push_back(i);
	}
	return neighbors;
}

void writeOutput(string fileName) {

	vector <vector <int> > finalAssignments;
	int k = -1;
	for(int i = 0; i < n; i++)
		k = max(k, label[i]);
	k += 2;
	finalAssignments.resize(k);

	for(int i = 0; i < n; i++) {
		finalAssignments[label[i] + 1].push_back(i);
	}
 
	ofstream outfile (fileName);
	for(int i = 1; i < k; i++) {
		outfile << "#" << i - 1 << endl;
		for(int j = 0; j < finalAssignments[i].size(); j++) {
			outfile << finalAssignments[i][j] << endl;
		}
	}
	if(finalAssignments[0].size() > 0) {
		outfile << "#outlier" << endl;
		for(int i = 0; i < finalAssignments[0].size(); i++)
			outfile << finalAssignments[0][i] << endl;
	}

	outfile.close();
}

int main(int argc, char* argv[]) {
	minPts = atoi(argv[1]);
	epsilon = atof(argv[2]);
	string inputfile = argv[3];

	readInput(inputfile);

	label.resize(n);
	for(int i = 0; i < n; i++)
		label[i] = -2;	// Undefined

	int cnt = -1;
	for(int i = 0; i < n; i++) {
		if(label[i] != -2) continue;
		vector <int> neighbors = rangeQuery(i);
		if(neighbors.size() < minPts) {
			label[i] = -1; // Noise
			continue;
		}
		cnt++;
		label[i] = cnt;
		vector <int> expand;
		for(int j = 0; j < neighbors.size(); j++)
			expand.push_back(neighbors[j]);
		 
		int idx = 0;
		while(idx < expand.size()) {
			int pt = expand[idx];
			if(label[pt] == -1) {
				label[pt] = cnt; // change noise to border point
				idx++;
				continue;
			}
			if(label[pt] != -2) { // previously processed
				idx++;	
				continue;
			}
			label[pt] = cnt;
			vector <int> neighbors2 = rangeQuery(pt);
			if(neighbors2.size() >= minPts) {
				for(int j = 0; j < neighbors2.size(); j++)
					expand.push_back(neighbors2[j]);
			}
			idx++;
		}
	}

	// Write output
	writeOutput("dbscan.txt");

	return 0;
}
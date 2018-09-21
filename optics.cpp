#include <bits/stdc++.h>
using namespace std;

typedef pair <double, int> PDI;
#define UNDEFINED -1

int minPts;
double eps;

int n, d;
vector <vector <double> > points;
vector <double> core_dist;
vector <bool> processed;
vector <double> reachability_dist;
vector <int> ordered_list;

void readInput(string fileName) {
	ifstream infile (fileName);
	string line;

	while(getline(infile, line)) {
		stringstream stream(line);
		vector <double> currPoint;
		while(true) {
			double coord;
			stream >> coord;
			if(!stream) break;
			currPoint.push_back(coord);
		}
		if(currPoint.size() > 0)
			points.push_back(currPoint);
	}

	infile.close();

	n = points.size();
	d = points[0].size();
}

void writeOutput(string fileName) {

	ofstream outfile (fileName);

	double val = 0;
	for(int i = 0; i < n; i++) {
		if(reachability_dist[i] != UNDEFINED)
			val = max(val, reachability_dist[i]);
	}
	for(int i = 0; i < n; i++) {
		if(reachability_dist[i] == UNDEFINED)
			reachability_dist[i] = 2 * val;
	}

	for(int i = 0; i < n; i++) {
		outfile << fixed << setprecision(20) << reachability_dist[ordered_list[i]] << endl;
	}

	outfile.close();
}

double distance_squared(vector<double> p1, vector<double> p2) {
	double dist = 0;

	for(int i = 0; i < p1.size(); i++) {
		double diff = p1[i] - p2[i];
		dist += diff * diff;
	}

	return dist;
}

vector <int> getNeighbors(int id) {
	vector <int> neighbors;
	double eps_sqr = eps * eps;

	for(int i = 0; i < n; i++) {
		if(distance_squared(points[id], points[i]) < eps_sqr)
			neighbors.push_back(i);
	}

	return neighbors;
}

void compute_core_distance() {
	core_dist.resize(n);

	for(int i = 0; i < n; i++) {
		vector <int> neighbors = getNeighbors(i);
		int num_neighbors = neighbors.size();

		if(num_neighbors < minPts) {
			core_dist[i] = UNDEFINED;
		}
		
		else {
			vector <double> neighbors_dist_sqr(num_neighbors);
			for(int j = 0; j < num_neighbors; j++)
				neighbors_dist_sqr[j] = distance_squared(points[i], points[neighbors[j]]);
			sort(neighbors_dist_sqr.begin(), neighbors_dist_sqr.end());
			core_dist[i] = sqrt(neighbors_dist_sqr[minPts - 1]);
		} 
	}
}

void update(vector <int> &neighbors, int id, priority_queue <PDI, vector<PDI>, greater<PDI> > &seeds) {
	double coredist = core_dist[id];
	for(auto it : neighbors) {
		if(processed[it]) continue;
		double new_reach_dist = max(coredist, sqrt(distance_squared(points[id], points[it])));
		if(reachability_dist[it] == UNDEFINED) { // points[it] not in seeds
			reachability_dist[it] = new_reach_dist;
			seeds.push(make_pair(new_reach_dist, it));
		}
		else { // points[it] in seeds, check for improvement
			if(new_reach_dist < reachability_dist[it]) {
				reachability_dist[it] = new_reach_dist;
				seeds.push(make_pair(new_reach_dist, it));
			}
		}
	}
}

int main(int argc, char* argv[]) {

	minPts = atoi(argv[1]);
	eps = atof(argv[2]);
	string inputFile = argv[3];

	readInput(inputFile);

	compute_core_distance();

	processed.resize(n);
	for(int i = 0; i < n; i++)
		processed[i] = false;

	reachability_dist.resize(n);
	for(int i = 0; i < n; i++)
		reachability_dist[i] = UNDEFINED;

	for(int i = 0; i < n; i++) {
		if(processed[i]) continue;
		
		vector <int> neighbors = getNeighbors(i);
		processed[i] = true;
		ordered_list.push_back(i);

		if(core_dist[i] == UNDEFINED) continue;

		priority_queue <PDI, vector<PDI>, greater<PDI> > seeds;
		update(neighbors, i, seeds);

		while(!seeds.empty()) {
			PDI top = seeds.top();
			seeds.pop();
			int q = top.second;
			if(reachability_dist[q] != top.first) continue;
			vector <int> neighbors2 = getNeighbors(q);
			processed[q] = true;
			ordered_list.push_back(q);
			if(core_dist[q] != UNDEFINED)
				update(neighbors2, q, seeds);
		}
	}

	writeOutput("optics.txt");

	return 0;
}
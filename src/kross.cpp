#include "kross.hpp"

using namespace std;

int main(int argc, char *argv[])
{
	srand (time(NULL)); // initialize the random number generator

	// read data from csv
	vector<Entry> data;
	read_leos(data);

	// construct class
	vector<Point> points;

	for(auto& row : data )
	{
		vector<double> values;
		values.push_back(row.f1);
		values.push_back(row.f2);
		points.push_back(Point(row.id, values, row.name));
	}

	// set K
	int K = 2;
	// set max_iter
	int max_iterations = 100;
	// set total points
	int total_points = points.size();
	// set total values
	int total_values = points[0].getTotalValues();
	
	// call method to execute k-means
	KMeans KM = KMeans(K, total_points, total_values, max_iterations);
	KM.run(points);

	return 0;
}

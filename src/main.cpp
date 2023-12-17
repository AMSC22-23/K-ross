#include "kross.hpp"

using namespace std;

int main(int argc, char *argv[])
{
	srand (time(NULL)); // initialize the random number generator

	// read data from csv
	vector<Entry> data;
	read_leos(data);

	// construct class
	Points_vect all_points;
	int count=0;
	for(auto& row : data )
	{
		vector<double> values;
		values.push_back(row.f1);
		values.push_back(row.f2);
		all_points.addPoint(Point(row.id, values, row.name));
		count++;
	}
	// set max_iter
	int max_iterations = 10000;

	// set total points
	int total_points = all_points.getNumberOfPoints();

	// set total values
	int total_values = all_points.getPoint(0).getNumberOfFeatures();

	// set K
	int K;
	cout << "Please enter the number of clusters: ";
	cin >> K;
	cout<< K << endl;
	
	while(K <= 0 || K > total_points)
	{
		cout << "The number of clusters must be greater than 0 and below the number of points" << endl;
		cout << "Please enter the number of clusters: ";
		cin >> K;
	}
	
	// call method to execute k-means
	KMeans KM = KMeans(K, total_points, total_values, max_iterations);
	KM.run(all_points);

	

	return 0;
}

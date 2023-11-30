#include <iostream>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>

#include "Kmeans.hpp"

using namespace std;

class Point
{
private:
	int id_point, id_cluster;
	vector<double> values; // values of the point's features
	int total_values; // number of features
	string name;

public:
	Point(int id_point, vector<double>& values, string name = "") // constructor
	{
		this->id_point = id_point;
		total_values = values.size(); // allocate the correct number of features

		for(int i = 0; i < total_values; i++)
			this->values.push_back(values[i]); // copy the values of the features

		this->name = name;
		id_cluster = -1; // not assigned to any cluster yet
	}

	int getID() // returns the id of the point
	{
		return id_point;
	}

	void setCluster(int id_cluster) // assigns the point to the cluster with the given id
	{
		this->id_cluster = id_cluster;
	}

	int getCluster() // returns the id of the cluster to which the point belongs
	{
		return id_cluster;
	}

	double getValue(int index) // returns the value of the feature with the given index
	{
		return values[index];
	}

	int getTotalValues() // returns the number of features
	{
		return total_values;
	}

	void addValue(double value) // adds a value to the list of features
	{
		values.push_back(value);
	}

	string getName() // returns the name of the point
	{
		return name;
	}
};

class Cluster
{
private:
	int id_cluster; // id of the cluster
	vector<double> central_values; // centroid of the cluster
	vector<Point> points; // points belonging to the cluster

public:
	Cluster(int id_cluster, Point point) // constructor
	{
		this->id_cluster = id_cluster;

		int total_values = point.getTotalValues(); // number of features of the point

		for(int i = 0; i < total_values; i++)
			central_values.push_back(point.getValue(i)); // set the centroid of the cluster with the values of the point

		points.push_back(point); // add the point to the list of points belonging to the cluster
	}

	void addPoint(Point point) // adds a point to the list of points belonging to the cluster
	{
		points.push_back(point);
	}

	// cluster.removePoint(point_id)

	bool removePoint(int id_point) // removes a point from the list of points belonging to the cluster
	{
		int total_points = points.size();

		for(int i = 0; i < total_points; i++)
		{
			if(points[i].getID() == id_point)
			{
				points.erase(points.begin() + i);
				return true;
			}
		}
		return false;
	}

	double getCentralValue(int index) // returns the centroid of the cluster
	{
		return central_values[index];
	}

	void setCentralValue(int index, double value) // sets the centroid of the cluster
	{
		central_values[index] = value;
	}

	Point getPoint(int index) // returns the point from the vector with the given index
	{
		return points[index];
	}

	int getTotalPoints() // returns the number of points belonging to the cluster
	{
		return points.size();
	}

	int getID() // returns the id of the cluster
	{
		return id_cluster;
	}
};

class KMeans
{
private:
	int K; // number of clusters
	int total_values, total_points, max_iterations; // number of features, number of points, maximum number of iterations
	vector<Cluster> clusters; // vector of clusters

	// return ID of nearest center (uses euclidean distance)
	int getIDNearestCenter(Point point) // returns the id of the nearest centroid to the given point
	{
		double sum = 0.0, min_dist;
		int id_cluster_center = 0;

		for(int i = 0; i < total_values; i++) // for each feature of the point
		{
			sum += pow(clusters[0].getCentralValue(i) -
					   point.getValue(i), 2.0);
		}

		min_dist = sqrt(sum);

		for(int i = 1; i < K; i++)
		{
			double dist;
			sum = 0.0;

			for(int j = 0; j < total_values; j++)
			{
				sum += pow(clusters[i].getCentralValue(j) -
						   point.getValue(j), 2.0);
			}

			dist = sqrt(sum);

			if(dist < min_dist)
			{
				min_dist = dist; // update the minimum distance with the one from the centroid it is working with
				id_cluster_center = i;
			}
		}

		return id_cluster_center;
	}

public:
	KMeans(int K, int total_points, int total_values, int max_iterations)
	{
		this->K = K;
		this->total_points = total_points;
		this->total_values = total_values;
		this->max_iterations = max_iterations;
	}

	void run(vector<Point> & points)
	{
		if(K > total_points)
			return;

		vector<int> prohibited_indexes;

		// Random selection of initial centroids
		for(int i = 0; i < K; i++)
		{
			while(true)
			{
				int index_point = rand() % total_points;

				// The find function is used to search for an element within a sequence. 
				// It takes as arguments two iterators that delimit the sequence and a value to search for.
				// It returns an iterator pointing to the found element, if present, or to the end iterator of the sequence if the element was not found.
				if(find(prohibited_indexes.begin(), prohibited_indexes.end(),
						index_point) == prohibited_indexes.end()) 
				{
					prohibited_indexes.push_back(index_point);
					points[index_point].setCluster(i);
					Cluster cluster(i, points[index_point]);
					clusters.push_back(cluster);
					break;
				}
			}
		}

		int iter = 1;

		while(true)
		{
			bool done = true;

			// Associates each point to the nearest center
			for(int i = 0; i < total_points; i++)
			{
				int id_old_cluster = points[i].getCluster(); // remember they were all -1 at the beginning
				int id_nearest_center = getIDNearestCenter(points[i]);

				if(id_old_cluster != id_nearest_center)
				{
					if(id_old_cluster != -1)
						clusters[id_old_cluster].removePoint(points[i].getID()); // remove from the old cluster as long as it is not -1

					points[i].setCluster(id_nearest_center); // update the cluster of the point
					clusters[id_nearest_center].addPoint(points[i]); // update the list of points belonging to the cluster
					done = false;
				}
			}

			// Recalculating the center of each cluster
			for(int i = 0; i < K; i++)
			{
				for(int j = 0; j < total_values; j++)
				{
					int total_points_cluster = clusters[i].getTotalPoints();
					double sum = 0.0;

					if(total_points_cluster > 0)
					{
						for(int p = 0; p < total_points_cluster; p++)
							sum += clusters[i].getPoint(p).getValue(j);
						clusters[i].setCentralValue(j, sum / total_points_cluster); // set the value of the j-th feature of the centroid of the i-th cluster
					}
				}
			}

			if(done == true || iter >= max_iterations)
			{
				cout << "Break in iteration " << iter << "\n\n";
				break;
			}

			iter++;
		}

		// Shows elements of clusters
		for(int i = 0; i < K; i++)
		{
			int total_points_cluster =  clusters[i].getTotalPoints();

			cout << "Cluster " << clusters[i].getID() + 1 << endl;
			for(int j = 0; j < total_points_cluster; j++)
			{
				cout << "Point " << clusters[i].getPoint(j).getID() + 1 << ": ";
				for(int p = 0; p < total_values; p++)
					cout << clusters[i].getPoint(j).getValue(p) << " ";

				string point_name = clusters[i].getPoint(j).getName();

				if(point_name != "")
					cout << "- " << point_name;

				cout << endl;
			}

			cout << "Cluster values: ";

			for(int j = 0; j < total_values; j++)
				cout << clusters[i].getCentralValue(j) << " ";

			cout << "\n\n";
		}
	}
};


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

#include <iostream>
#include <vector>
#include "point.hpp"

#include "cluster.hpp"


using namespace std;


	Cluster::Cluster(int id_cluster, Point point) // constructor
	{
		this->id_cluster = id_cluster;

		int total_values = point.getTotalValues(); // number of features of the point

		for(int i = 0; i < total_values; i++)
			central_values.push_back(point.getValue(i)); // set the centroid of the cluster with the values of the point

		points.push_back(point); // add the point to the list of points belonging to the cluster
	}

	void Cluster::addPoint(Point point) // adds a point to the list of points belonging to the cluster
	{
		points.push_back(point);
	}

	// cluster.removePoint(point_id)

	bool Cluster::removePoint(int id_point) // removes a point from the list of points belonging to the cluster
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

	double Cluster::getCentralValue(int index) // returns the centroid of the cluster
	{
		return central_values[index];
	}

	//@note: you may cache this result among the private attributes to avoid computations
	vector<vector<double>> Cluster::getCentralValueCoordinates() // returns the centroid of the cluster
	{
		vector<vector<double>> coordinates;
		coordinates.push_back(central_values);
		return coordinates;
	}

	void Cluster::setCentralValue(int index, double value) // sets the centroid of the cluster
	{
		central_values[index] = value;
	}

	Point Cluster::getPoint(int index) // returns the point from the vector with the given index
	{
		return points[index];
	}

	int Cluster::getTotalPoints() // returns the number of points belonging to the cluster
	{
		return points.size();
	}

	int Cluster::getID() // returns the id of the cluster
	{
		return id_cluster;
	}

	//@note: you may cache this result among the private attributes to avoid computations
	vector<vector<double>> Cluster::getPointsCoordinates()
	{
		vector<vector<double>> points_coordinates;
		// cout << "points_coordinates.size() ZACCANASTA= " << points_coordinates.size() << endl;
		for (auto point : this->points)
		{
			points_coordinates.push_back(point.getValues());	
		}

		return points_coordinates;
	}

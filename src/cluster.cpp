#include <iostream>
#include <vector>
#include "cluster.hpp"


using namespace std;


	Cluster::Cluster(int newid_cluster, Point newCentroid)
	{
		id_cluster = newid_cluster;

		int total_values = newCentroid.getNumberOfFeatures(); 

		for(int i = 0; i < total_values; i++)
		{
			centroid = newCentroid;
		}
		cluster_points.addPoint(newCentroid); //!!!
	}

	void Cluster::addPoint(Point point)
	{
		cluster_points.addPoint(point);
	}

	void Cluster::removePointFromCluster(int id_point) // removes a point from the list of points belonging to the cluster
	{
		cluster_points.removePoint(id_point);
	}

	Point Cluster::getCentroid() // returns the centroid of the cluster
	{
		return centroid;
	}
	vector<vector<double>> Cluster::getCentroidCoordinates() // returns the centroid of the cluster
	{
		return centroid.getPointsCoordinates();
	}

	void Cluster::setCentroid(int index, double value) // sets the centroid of the cluster
	{
		centroid.setValue(index, value);
	}

	Point Cluster::getPoint(int index) // returns the point from the vector with the given index
	{
		return cluster_points.getPoint(index);
	}

	int Cluster::getTotalPoints() // returns the number of points belonging to the cluster
	{
		return cluster_points.getNumberOfPoints();
	}

	int Cluster::getID() // returns the id of the cluster
	{
		return id_cluster;
	}

	vector<vector<double>> Cluster::getClusterPointsCoordinates()
	{
		return cluster_points.getPointsCoordinates();
	}

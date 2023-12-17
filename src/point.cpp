#include <iostream>
#include <vector>
#include <cmath>

#include "point.hpp"



using namespace std;


	Point::Point(int id_point, vector<double>& values, string name) // constructor
	{
		this->id_point = id_point;
		number_of_features = values.size(); // allocate the correct number of features

		for(int i = 0; i < number_of_features; i++)
			this->values.push_back(values[i]); // copy the values of the features

		this->name = name;
		id_cluster = -1; // not assigned to any cluster yet
	}

	int Point::getID() // returns the id of the point
	{
		return id_point;
	}

	void Point::setCluster(int id) // assigns the point to the cluster with the given id
	{
		this->id_cluster = id;
	}

	int Point::getCluster() // returns the id of the cluster to which the point belongs
	{
		return id_cluster;
	}

	double Point::getValue(int index) // returns the value of the feature with the given index
	{
		return values[index];
	}

	int Point::getNumberOfFeatures() // returns the number of features
	{
		return number_of_features;
	}

	void Point::addValue(double value) // adds a value to the list of features
	{
		values.push_back(value);
	}

	string Point::getName() // returns the name of the point
	{
		return name;
	}

	vector<double> Point::getValues() // returns the vector of features
	{
		return values;
	}

	vector<vector<double>> Point::getPointsCoordinates(){
		vector<vector<double>> points_coordinates;
		vector<double> point_coordinates;
		for(int j = 0; j < number_of_features; j++)
			point_coordinates.push_back(values[j]);
		points_coordinates.push_back(point_coordinates);
		return points_coordinates;
	}

	void Point::setValue(int index, double value){
		values[index] = value;
	}

	double Point::euclidianDistanceBetweenPoints(Point point1, Point point2){
		double sum = 0.0;
		for(int i = 0; i < point1.getNumberOfFeatures(); i++)
			sum += pow(point1.getValue(i) - point2.getValue(i), 2.0);
		return sqrt(sum);
	}


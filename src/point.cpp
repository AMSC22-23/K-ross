#include <iostream>
#include <vector>

#include "point.hpp"



using namespace std;


	Point::Point(int id_point, vector<double>& values, string name) // constructor
	{
		this->id_point = id_point;
		total_values = values.size(); // allocate the correct number of features

		//@note: you can simply do this->values = values
		//       moreover the fact that they have the same name is very confunsing
		//       should use some convetion. e.g. all class members have a prefix `m_`
		for(int i = 0; i < total_values; i++)
			this->values.push_back(values[i]); // copy the values of the features

		this->name = name;
		id_cluster = -1; // not assigned to any cluster yet
	}

	int Point::getID() // returns the id of the point
	{
		return id_point;
	}

	void Point::setCluster(int id_cluster) // assigns the point to the cluster with the given id
	{
		this->id_cluster = id_cluster;
	}

	int Point::getCluster() // returns the id of the cluster to which the point belongs
	{
		return id_cluster;
	}

	double Point::getValue(int index) // returns the value of the feature with the given index
	{
		return values[index];
	}

	int Point::getTotalValues() // returns the number of features
	{
		return total_values;
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


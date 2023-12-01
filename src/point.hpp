#ifndef POINT_HPP
#define POINT_HPP


#include <iostream>
#include <vector>

using namespace std;

class Point
{
private:
    int id_point, id_cluster;
    vector<double> values; // values of the point's features
    int total_values; // number of features
    string name;

public:
    Point(int id_point, vector<double>& values, string name = ""); // constructor

    int getID(); // returns the id of the point

    void setCluster(int id_cluster); // assigns the point to the cluster with the given id

    int getCluster(); // returns the id of the cluster to which the point belongs

    double getValue(int index); // returns the value of the feature with the given index

    int getTotalValues(); // returns the number of features

    void addValue(double value); // adds a value to the list of features

    string getName(); // returns the name of the point

    vector<double> getValues();
};



#endif
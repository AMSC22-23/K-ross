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
    //@note: why you need it? is it not the same of values.size()?
    int total_values; // number of features
    //@note: you do not need a string here, an integer that represent the category
    //       would have been much lighter
    string name;

public:
    //@note: the reference should be const
    Point(int id_point, vector<double>& values, string name = ""); // constructor

    //@note: const!
    int getID(); // returns the id of the point

    void setCluster(int id_cluster); // assigns the point to the cluster with the given id

    //@note: const!
    int getCluster(); // returns the id of the cluster to which the point belongs

    double getValue(int index); // returns the value of the feature with the given index

    //@note: const!
    int getTotalValues(); // returns the number of features

    void addValue(double value); // adds a value to the list of features

    //@note: const!
    string getName(); // returns the name of the point

    //@note: const!
    vector<double> getValues();
};



#endif
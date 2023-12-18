#ifndef CLUSTER_HPP
#define CLUSTER_HPP


#include <iostream>
#include <vector>
#include "point.hpp"

using namespace std;


class Cluster
{
private:
    int id_cluster; // id of the cluster
    vector<double> central_values; // centroid of the cluster
    //@note: since each point has an ID, instead of storing a copy
    //       of each point you could store just its ID and a 
    //       const reference to a list of all the points
    vector<Point> points; // points belonging to the cluster

public:
    //@note: should pass by const reference 
    Cluster(int id_cluster, Point point);
    //@note: should pass by const reference 
    void addPoint(Point point);
    bool removePoint(int id_point);
    //@note: const!
    double getCentralValue(int index);
    void setCentralValue(int index, double value);
    //@note: const!
    Point getPoint(int index);
    int getTotalPoints();
    int getID();
    vector<vector<double>> getPointsCoordinates();
    vector<vector<double>> getCentralValueCoordinates();
};


#endif
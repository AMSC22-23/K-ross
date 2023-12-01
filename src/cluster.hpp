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
    vector<Point> points; // points belonging to the cluster

public:
    Cluster(int id_cluster, Point point);
    void addPoint(Point point);
    bool removePoint(int id_point);
    double getCentralValue(int index);
    void setCentralValue(int index, double value);
    Point getPoint(int index);
    int getTotalPoints();
    int getID();
    vector<vector<double>> getPointsCoordinates();
    vector<vector<double>> getCentralValueCoordinates();
};


#endif
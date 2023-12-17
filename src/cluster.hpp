#include <iostream>
#include <vector>
#include "point.hpp"
#include "points_vect.hpp"

using namespace std;


class Cluster
{
private:
    int id_cluster = -1; // id of the cluster
    Point centroid; // centroid of the cluster
    Points_vect cluster_points; // points belonging to the cluster

public:
    Cluster(int id_cluster, Point newCentroid);
    Cluster() = default;
    void addPoint(Point point);
    void removePointFromCluster(int id_point);
    Point getCentroid();
    void setCentroid(int index, double value);
    Point getPoint(int index);
    int getTotalPoints();
    int getID();
    vector<vector<double>> getClusterPointsCoordinates();
    vector<vector<double>> getCentroidCoordinates();
};
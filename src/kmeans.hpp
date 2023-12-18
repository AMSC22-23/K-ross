#ifndef KMEANS_HPP
#define KMEANS_HPP


#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include "cluster.hpp"

using namespace std; 

class KMeans
{
private:
    int K; // number of clusters
    int total_values, total_points, max_iterations; // number of features, number of points, maximum number of iterations
    vector<Cluster> clusters; // vector of clusters

    //@note: should pass by const reference 
    int getIDNearestCenter(Point point);

public:
    KMeans(int K, int total_points, int total_values, int max_iterations);

    //@note: pass by const reference, creating a clustering should not change the dataset
    void run(vector<Point> & points);
};

#endif
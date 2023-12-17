#ifndef KMEANS_HPP
#define KMEANS_HPP


#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include "cluster.hpp"
#include "point.hpp"
#include "points_vect.hpp"
#include "gnuplot-iostream.h"

using namespace std; 

class KMeans
{
private:
    int K; // number of clusters
    Gnuplot gp; // gnuplot object
    bool changed; // true if at least one point has changed cluster
    std::string plotInstruction; // gnuplot instruction
    int number_of_features, number_of_points, max_iterations; // number of features, number of points, maximum number of iterations
    vector<Cluster> clusters; // vector of clusters
    // Functions
    int getIDNearestCenter(Point point);
    void selectRandomCentroids(Points_vect & all_points);
    void associatePointsToClusters(Points_vect & all_points);
    void setplotIntruction(int number_of_clusters);
    void printClusters();
    void calculateCentroids();
    void plotClusters(int number_of_clusters);

public:
    KMeans(int K, int total_points, int total_values, int max_iterations);

    void run(Points_vect & all_points);
};

#endif
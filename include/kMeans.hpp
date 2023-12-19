#ifndef KMEANS_HPP
#define KMEANS_HPP

#include <random>
#include <iostream>
#include <mpi.h>
#include <thread>
#include "gnuplot-iostream.h"
#include "point.hpp"



class KMeans
{
public:
    KMeans(int k, std::vector<Point> &points);

    void run(int rank, int world_size);
    //@note: const method
    void printClusters();
    void plotClusters();
private:
    int k;
    std::vector<Point> points;
    std::vector<Point> centroids;
    //@note: strong coupling between plotting and the algorithm is a questionable choice
    Gnuplot gp;
};


#endif // KMEANS_HPP
#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <fstream>
#include <sstream>
#include <random>
#include "gnuplot-iostream.h"
#include <thread>
#include <random>
#include <mpi.h>
#include <chrono>

#include "point.hpp"
#include "kMeans.hpp"
#include "csvReader.hpp"


int main()
{
    MPI_Init(NULL, NULL);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    //std::cout << "Rank: " << rank << std::endl;

    CSVReader reader("./Files/profiling.csv");
    std::vector<Point> points = reader.readData();
    int k;
    if (rank == 0)
    {
        std::cout << "Enter the number of clusters: ";
        std::cin >> k;
        while(k<0 || k > points.size())
        {
            std::cout << "Enter the number of clusters: ";
            std::cin >> k;
        }
    }

    MPI_Bcast(&k, 1, MPI_INT, 0, MPI_COMM_WORLD);
        
    KMeans kmeans(k, points);
    auto start = std::chrono::high_resolution_clock::now();
    kmeans.run(rank, world_size);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    if (rank == 0)
        std::cout << "Time: " << elapsed.count() << " s" << std::endl;
    if (rank == 0)
    {
        //kmeans.printClusters();
        if (k <= 8)
            kmeans.plotClusters();

    }
    MPI_Finalize();
}
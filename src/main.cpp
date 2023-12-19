#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <fstream>
#include <sstream>
#include <random>
#include "../include/gnuplot-iostream.h"
#include <thread>
#include <random>
#include <mpi.h>
#include "../include/point.hpp"
#include "../include/kMeans.hpp"
#include "../include/csvReader.hpp"


int main()
{
    //@note: should use argc, argv. 
    //       More importantly in C++ at least use `nullptr` instead of `NULL`
    MPI_Init(NULL, NULL);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    //std::cout << "Rank: " << rank << std::endl;

    //@note: file name could have been read from executable arguments
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
    kmeans.run(rank, world_size);
    if (rank == 0)
    {
        kmeans.printClusters();
        if (k <= 8)
            kmeans.plotClusters();

    }
    MPI_Finalize();
}
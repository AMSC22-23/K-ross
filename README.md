# Kmeans
This project is an implementation of the K-Means clustering algorithm in C++. It reads data from CSV files, performs K-Means clustering on the data, and generates an animation of the clustering process.

## Getting Started
To compile the project, navigate to the project  root directory in your terminal and run the following command:

```bash
make
```
This will compile the source files and link them into an executable named <kbd>exe</kbd> that will be created in the project root folder.


You then run the <kbd>exe</kbd> with
```bash
mpirun -n num_of_processes ./exe
```
set num_of_processes as you prfefer.


## What to expect
When running the program, there are a few limitations to keep in mind:

1. The program currently supports reading and processing only CSV files with two features. If you have a different number of features in your CSV file, the program may not work as expected.

2. The program uses the Gnuplot library to generate visualizations of the clusters. However, please note that the program will only generate plots for up to 8 clusters. If you set the number of clusters (k) to a value greater than 8, the program will only print the cluster information on the terminal without generating any plots.

Please ensure that your CSV files have two features and consider setting the number of clusters within the limit of 8 to get the desired visualizations.


## Project Structure
The project is organized as follows:
* Files/: This directory contains the CSV files that are used as input data for the program. The provided files are Precolombian.csv and profiling.csv.

* IMG/: This directory contains the images that are generated by the program to visualize the clustering process. These images are used to construct the animation.

* include/: This directory contains the header files for the project. These define the classes and functions that are used in the program.

* src/: This directory contains the source files for the project. These implement the classes and functions that are defined in the header files.

The project also includes a Makefile for compiling and linking the program, and a .gitignore file for specifying which files and directories should be ignored by Git.

## Algorithm
The K-Means clustering algorithm works as follows:

1. Initialize k centroids randomly by selecting k points from the input data.
2. Assign each point to the cluster whose centroid is nearest.
3. Update the centroids based on the points assigned to each cluster.
4. Repeat steps 2 and 3 until no point changes its cluster assignment or the maximum number of iterations is reached.

The algorithm is implemented in the KMeans class, which is defined in include/kMeans.hpp and implemented in src/kMeans.cpp. The KMeans class also includes methods for printing the clusters and for generating a plot of the clusters using the Gnuplot library.

## Authors
Leognazio Pagliochini - Francesco Rosnati - Riccardo Selis
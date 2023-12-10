#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <string>
#include <cmath>

#include <chrono>
#include <thread>

#include "cluster.hpp"

#include "kmeans.hpp"
#include "gnuplot-iostream.h"

using namespace std; 
	
	// return ID of nearest center (uses euclidean distance)
	int KMeans::getIDNearestCenter(Point point) // returns the id of the nearest centroid to the given point
	{
		
		double sum = 0.0, min_dist;
		int id_cluster_center = 0;

		for(int i = 0; i < total_values; i++) // for each feature of the point
		{
			sum += pow(clusters[0].getCentralValue(i) -
					   point.getValue(i), 2.0);
		}

		min_dist = sqrt(sum);

		for(int i = 1; i < K; i++)
		{
			double dist;
			sum = 0.0;

			for(int j = 0; j < total_values; j++)
			{
				sum += pow(clusters[i].getCentralValue(j) -
						   point.getValue(j), 2.0);
			}

			dist = sqrt(sum);

			if(dist < min_dist)
			{
				min_dist = dist; // update the minimum distance with the one from the centroid it is working with
				id_cluster_center = i;
			}
		}

		return id_cluster_center;
	}

	KMeans::KMeans(int K, int total_points, int total_values, int max_iterations)
	{
		this->K = K;
		this->total_points = total_points;
		this->total_values = total_values;
		this->max_iterations = max_iterations;
	}

	void KMeans::run(vector<Point> & points)
	
	{
		// added by soldier for debugging purposes:
		int kappa = 0;
		

		if(K > total_points)
			return;

		vector<int> prohibited_indexes;

		Gnuplot gp;
		gp << "set xrange [20:70]\nset yrange [0:30]\n";
		

//---------------------Da runnare in paralllo--------------------------------------
//---------------------------------------------------------------------------------
		
		// Random selection of initial centroids
		for(int i = 0; i < K; i++)
		{
			while(true)
			{
				int index_point = rand() % total_points;

				// The find function is used to search for an element within a sequence. 
				// It takes as arguments two iterators that delimit the sequence and a value to search for.
				// It returns an iterator pointing to the found element, if present, or to the end iterator of the sequence if the element was not found.
				if(find(prohibited_indexes.begin(), prohibited_indexes.end(),
						index_point) == prohibited_indexes.end()) 
				{
					prohibited_indexes.push_back(index_point);
					points[index_point].setCluster(i);
					Cluster cluster(i, points[index_point]);
					clusters.push_back(cluster);
					break;
				}
			}
		}
//---------------------------------------------------------------------------------
		int iter = 1;

		while(true)
		{
			bool done = true;

//---------------------Da NON runnare in paralllo----------------------------------
//---------------------------------------------------------------------------------
			// Associates each point to the nearest center
			for(int i = 0; i < total_points; i++)
			{
				int id_old_cluster = points[i].getCluster(); // remember they were all -1 at the beginning
				int id_nearest_center = getIDNearestCenter(points[i]);

				if(id_old_cluster != id_nearest_center)
				{
					if(id_old_cluster != -1)
						clusters[id_old_cluster].removePoint(points[i].getID()); // remove from the old cluster as long as it is not -1

					points[i].setCluster(id_nearest_center); // update the cluster of the point
					clusters[id_nearest_center].addPoint(points[i]); // update the list of points belonging to the cluster
					done = false;
				}
			}
//---------------------------------------------------------------------------------

			std::string gnuplotcommand = "plot";
			
//---------------------Da NON runnare in paralllo----------------------------------
//---------------------------------------------------------------------------------

			// ciclo per definire gnuplot command
			for(int i = 0; i < K; i++)
			{
				std::string color;
				switch (i) {
					case 0:
						color = "red";
						break;
					case 1:
						color = "blue";
						break;
					case 2:
						color = "green";
						break;
					case 3:
						color = "purple";
						break;
					case 4:
						color = "cyan";
						break;
					case 5:
						color = "brown";
						break;
					case 6:
						color = "yellow";
						break;
					case 7:
						color = "orange";
						break;

					default:
						color = "Unknown";
						break;
				}

				if(i != 0)
					gnuplotcommand += ",";
				gnuplotcommand += " '-' with points title 'Cluster ";
				gnuplotcommand += std::to_string(i+1);
				gnuplotcommand += "' pt 7 lc rgb '";
				gnuplotcommand += color;
				gnuplotcommand += "'";
				if(i==K-1){
					gnuplotcommand += ", '-' with points title 'Centroids' pt 5 ps 2 lc rgb 'black'";
				}
				else {
					gnuplotcommand += ", '-' with points notitle pt 5 ps 2 lc rgb 'black'";
				}
				if(i == K-1)
					gnuplotcommand += "\n";
			}
			gp<<gnuplotcommand;
//---------------------------------------------------------------------------------


//---------------------Da runnare in paralllo--------------------------------------
//---------------------------------------------------------------------------------

			// Recalculating the center of each cluster
			for(int i = 0; i < K; i++)
			{
							
				for(int j = 0; j < total_values; j++)
				{
					int total_points_cluster = clusters[i].getTotalPoints();
					double sum = 0.0;

					if(total_points_cluster > 0)
					{
						for(int p = 0; p < total_points_cluster; p++)
							sum += clusters[i].getPoint(p).getValue(j);
						clusters[i].setCentralValue(j, sum / total_points_cluster); // set the value of the j-th feature of the centroid of the i-th cluster
					}
				}
				gp.send1d(clusters.at(i).getPointsCoordinates());
				gp.send1d(clusters.at(i).getCentralValueCoordinates());
			}
//---------------------------------------------------------------------------------


			std::chrono::milliseconds duration(300);
			std::this_thread::sleep_for(duration);
			cout << "Iteration number: " << iter << endl;
			if(done == true || iter >= max_iterations)
			{
				cout << "Break in iteration " << iter << "\n\n";
				break;
			}
			
			iter++;
		}

/*
		// Shows elements of clusters
		for(int i = 0; i < K; i++)
		{
			int total_points_cluster =  clusters[i].getTotalPoints();

			cout << "Cluster " << clusters[i].getID() + 1 << endl;
			for(int j = 0; j < total_points_cluster; j++)
			{
				cout << "Point " << clusters[i].getPoint(j).getID() + 1 << ": ";
				for(int p = 0; p < total_values; p++)
					cout << clusters[i].getPoint(j).getValue(p) << " ";

				string point_name = clusters[i].getPoint(j).getName();

				if(point_name != "")
					cout << "- " << point_name;

				cout << endl;
			}

			cout << "Cluster values: ";

			for(int j = 0; j < total_values; j++)
				cout << clusters[i].getCentralValue(j) << " ";

			cout << "\n\n";
		}


*/

		// Gnuplot gp;
		// gp << "set xrange [20:70]\nset yrange [0:30]\n";
		// gp << "plot '-' with points title 'Cluster 1' pt 6 lc rgb 'blue', '-' with points title 'Cluster 2' pt 6 lc rgb 'red', '-' with points pt 11 ps 3 lc rgb 'black', '-' with points pt 11 ps 3 lc rgb 'black'\n";
		// gp.send1d(clusters[0].getPointsCoordinates());
		// gp.send1d(clusters[1].getPointsCoordinates());
		// gp.send1d(clusters[0].getCentralValueCoordinates());
		// gp.send1d(clusters[1].getCentralValueCoordinates());
		// gp << "e\n";
	}

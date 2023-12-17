#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <string>
#include <cmath>

#include <chrono>
#include <thread>

#include "kmeans.hpp"


using namespace std; 

	KMeans::KMeans(int K, int number_of_points, int number_of_features, int max_iterations)
	{
		this->K = K;
		this->number_of_points = number_of_points;
		this->number_of_features = number_of_features;
		this->max_iterations = max_iterations;
	}

	int KMeans::getIDNearestCenter(Point point) // returns the id of the nearest centroid to the given point
	{
		double min_dist = 0.0;
		int id_cluster_center = 0;

		for (int i = 0; i < K; i++) {
			double dist = point.euclidianDistanceBetweenPoints(point, clusters[i].getCentroid());
			if (i == 0) {
				min_dist = dist;
			}
			else {
				if (dist < min_dist) {
					min_dist = dist;
					id_cluster_center = i;
				}
			}
		}
		return id_cluster_center;
	}

	void KMeans::selectRandomCentroids(Points_vect & all_points) // parallelizzabile
	{
		vector<int> prohibited_indexes;
		for (int i = 0 ; i < K ; i++)
		{
			while (true)
			{
				int index_point = rand() % number_of_points;
				if(find(prohibited_indexes.begin(), prohibited_indexes.end(), index_point) == prohibited_indexes.end()) 
				{
					prohibited_indexes.push_back(index_point);
					all_points.getPoint(index_point).setCluster(i);
					Cluster cluster(i, all_points.getPoint(index_point));
					clusters.push_back(cluster);
					break;
				}
			}
		}
	}

	void KMeans::associatePointsToClusters(Points_vect & all_points) // the function returns true if the assignment of points to clusters has changed from the previous iteration
	{
		changed = false;

		for(int i = 0 ; i < number_of_points ; i++)
		{
			int old_cluster = all_points.getPoint(i).getCluster();
			int nearest_cluster = getIDNearestCenter(all_points.getPoint(i));
			if (old_cluster != nearest_cluster)
			{
				cout << "Point " << i + 1 << " changed cluster from " << old_cluster + 1 << " to " << nearest_cluster + 1 << endl;
				if(old_cluster != -1)
					clusters[old_cluster].removePointFromCluster(all_points.getPoint(i).getID());
				all_points.getPoint(i).setCluster(nearest_cluster);
				clusters[nearest_cluster].addPoint(all_points.getPoint(i));
				changed = true;
			}
		}
	}

	void KMeans::setplotIntruction(int number_of_clusters)
	{
		if(number_of_clusters > 8)
			return;
		std::string gnuplotcommand = "plot";
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
						color = "pink";
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
			Gnuplot gp;
			gp << "set xrange [20:70]\nset yrange [0:30]\n";
			plotInstruction = gnuplotcommand;
	}
	
	void KMeans::plotClusters(int number_of_clusters)
	{
		if(number_of_clusters > 8)
			return;
		gp << plotInstruction;
		for(int i = 0; i < K; i++)
		{
			gp.send1d(clusters.at(i).getClusterPointsCoordinates());
			gp.send1d(clusters.at(i).getCentroidCoordinates());
		}
		std::chrono::milliseconds duration(300); //timer to visualize the animation
		std::this_thread::sleep_for(duration);
	}

	void KMeans::printClusters()
	{
		for(int i = 0; i < K; i++)
		{
			cout << "Cluster " << clusters[i].getID() + 1 << endl;
			for(int j = 0; j < clusters[i].getTotalPoints(); j++)
			{
				cout << "Point " << clusters[i].getPoint(j).getID() + 1 << ": ";
				for(int p = 0; p < number_of_features; p++)
					cout << clusters[i].getPoint(j).getValue(p) << " ";

				string point_name = clusters[i].getPoint(j).getName();

				if(point_name != "")
					cout << "- " << point_name;

				cout << endl;
			}

			cout << "Cluster values: ";

			for(int j = 0; j < number_of_features; j++)
				cout << clusters[i].getCentroid().getValue(j) << " ";

			cout << "\n\n";
		}
	}

	void KMeans::calculateCentroids()
	{
		for(int i = 0; i < K; i++)
		{
			for(int j = 0; j < number_of_features; j++)
			{
				int total_points_cluster = clusters.at(i).getTotalPoints();
				double sum = 0.0;

				if(total_points_cluster > 0)
				{
					for(int p = 0; p < total_points_cluster; p++)
						sum += clusters[i].getPoint(p).getValue(j);
					clusters[i].setCentroid(j, sum / total_points_cluster);
				}
			}
		}
	}

	void KMeans::run(Points_vect & all_points)
	{
		if(K > number_of_points)
			return;
		selectRandomCentroids(all_points);

		cout<<"Centroids initialized"<<endl;

		changed = true;
		int iter = 1;

		setplotIntruction(K);

		while(changed && iter < max_iterations)
		{
			cout << "Iteration: " << iter << endl;

			associatePointsToClusters(all_points);

			calculateCentroids();

			plotClusters(K);

			iter++;
		}
		printClusters();

		std::cout << "The algorithm converged after " << iter << " iterations." << std::endl;
	}
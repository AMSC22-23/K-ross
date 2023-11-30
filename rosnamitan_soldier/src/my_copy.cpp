// Implementation of the KMeans Algorithm
// reference: http://mnemstudio.org/clustering-k-means-example-1.htm

#include <iostream>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>

#include "my_copy.hpp"


using namespace std;

class Point
{
private:
	int id_point, id_cluster;
	vector<double> values; // valori delle features del punto
	int total_values; // numero di features
	string name; 

public:
	Point(int id_point, vector<double>& values, string name = "") //costruttore 
	{
		this->id_point = id_point;
		total_values = values.size(); // alloca il giusto numero di features

		for(int i = 0; i < total_values; i++)
			this->values.push_back(values[i]); // copia i valori delle features

		this->name = name;
		id_cluster = -1; // ancora non è stato assegnato a nessun cluster
	}

	int getID() // restituisce l'id del punto
	{
		return id_point;
	}

	void setCluster(int id_cluster) //assegna il punto al cluster con l'id passato come parametro
	{
		this->id_cluster = id_cluster;
	}

	int getCluster() // restituisce l'id del cluster a cui appartiene il punto
	{
		return id_cluster;
	}

	double getValue(int index) // restituisce il valore della feature con l'indice passato come parametro
	{
		return values[index];
	}

	int getTotalValues() // restituisce il numero di features
	{
		return total_values;
	}

	void addValue(double value) // aggiunge un valore alla lista di features
	{
		values.push_back(value);
	}

	string getName() // restituisce il nome del punto
	{
		return name;
	}

};

class Cluster
{
private:
	int id_cluster; // id del cluster
	vector<double> central_values; // centroide del cluster
	vector<Point> points; //punti appartenenti al cluster

public:
	Cluster(int id_cluster, Point point) // costruttore
	{
		this->id_cluster = id_cluster;

		int total_values = point.getTotalValues(); // numero di features del punto

		for(int i = 0; i < total_values; i++)
			central_values.push_back(point.getValue(i)); //setta il centroide del cluster con i valori del punto

		points.push_back(point); // aggiunge il punto alla lista dei punti appartenenti al cluster !!!
	}

	void addPoint(Point point) // aggiunge un punto alla lista dei punti appartenenti al cluster
	{
		points.push_back(point);
	}

	// nomecluster.removePoint(id_punto) 

	bool removePoint(int id_point) // rimuove un punto dalla lista dei punti appartenenti al cluster
	{
		int total_points = points.size(); 

		for(int i = 0; i < total_points; i++)
		{
			if(points[i].getID() == id_point)
			{
				points.erase(points.begin() + i);
				return true;
			}
		}
		return false;
	}

	double getCentralValue(int index) // centroide del cluster
	{
		return central_values[index];
	}

	void setCentralValue(int index, double value) // setta il centroide del cluster
	{
		central_values[index] = value;
	}

	Point getPoint(int index) // restituisce il punto del vattore con l'indice passato come parametro
	{
		return points[index];
	}

	int getTotalPoints() // restituisce il numero di punti appartenenti al cluster
	{
		return points.size(); 
	}

	int getID() // restituisce l'id del cluster 
	{
		return id_cluster;
	}
};

class KMeans
{
private:
	int K; // numero di cluster
	int total_values, total_points, max_iterations; // numero di features, numero di punti, numero massimo di iterazioni
	vector<Cluster> clusters; // vettore di cluster

	// return ID of nearest center (uses euclidean distance)
	int getIDNearestCenter(Point point) // restituisce l'id del centroide più vicino al punto passato come parametro
	{
		double sum = 0.0, min_dist;
		int id_cluster_center = 0;

		for(int i = 0; i < total_values; i++) // per ogni features del punto
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
				min_dist = dist; // aggiorna la distanza minima con quella dal centroide con cui sta lavorando 
				id_cluster_center = i;
			}
		}

		return id_cluster_center;
	}

public:
	KMeans(int K, int total_points, int total_values, int max_iterations)
	{
		this->K = K;
		this->total_points = total_points;
		this->total_values = total_values;
		this->max_iterations = max_iterations;
	}

	void run(vector<Point> & points)
	{
		if(K > total_points)
			return;

		vector<int> prohibited_indexes;

		// Scelta casuale dei centroidi iniziali
		for(int i = 0; i < K; i++)
		{
			while(true)
			{
				int index_point = rand() % total_points;
\
				if(find(prohibited_indexes.begin(), prohibited_indexes.end(),
						index_point) == prohibited_indexes.end()) // La funzione find viene utilizzata 
						// per cercare un elemento all'interno di una sequenza. Prende come argomenti due 
						// iteratori che delimitano la sequenza e un valore da cercare. Restituisce un iteratore 
						// che punta all'elemento trovato, se presente, o all'iteratore di fine sequenza se l'elemento 
						// non è stato trovato.
						
				{
					prohibited_indexes.push_back(index_point);
					points[index_point].setCluster(i);
					Cluster cluster(i, points[index_point]);
					clusters.push_back(cluster);
					break;
				}
			}
		}

		int iter = 1;

		while(true)
		{
			bool done = true;

			// associates each point to the nearest center
			for(int i = 0; i < total_points; i++)
			{
				int id_old_cluster = points[i].getCluster(); // remind erano tutti a -1 all'inizio
				int id_nearest_center = getIDNearestCenter(points[i]);

				if(id_old_cluster != id_nearest_center)
				{
					if(id_old_cluster != -1)
						clusters[id_old_cluster].removePoint(points[i].getID()); // toglie dal cluster vecchio a patto che non si a -1 

					points[i].setCluster(id_nearest_center); // aggiorna il cluster del punto
					clusters[id_nearest_center].addPoint(points[i]); // aggiorna l'elenco dei punti appartenenti al cluster
					done = false;
				}
			}

			// recalculating the center of each cluster
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
						clusters[i].setCentralValue(j, sum / total_points_cluster); // piazza il valore dell feature
						// j-esima del centroide del cluster i-esimo
					}
				}
			}

			if(done == true || iter >= max_iterations)
			{
				cout << "Break in iteration " << iter << "\n\n";
				break;
			}

			iter++;
		}

		// shows elements of clusters
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
	}
};


int main(int argc, char *argv[])
{
	srand (time(NULL)); // inizializza il generatore di numeri casuali

	// read data from csv
	vector<Entry> data;
	read_leos(data);

	// construct class
	vector<Point> points;

	for(auto& row : data )
	{
		vector<double> values;
		values.push_back(row.f1);
		values.push_back(row.f2);
		points.push_back(Point(row.id, values, row.name));
	}



	// set K
	int K = 16;
	// set max_iter
	int max_iterations = 100;
	// set total points
	int total_points = points.size();
	// set total values
	int total_values = points[0].getTotalValues();
	
	// call method to execute k-means
	KMeans KM = KMeans(K, total_points, total_values, max_iterations);
	KM.run(points);





	return 0;
}

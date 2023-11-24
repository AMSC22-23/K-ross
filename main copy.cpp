#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

// Funzione per calcolare la distanza euclidea tra due punti
double distance(const std::vector<double>& point1, const std::vector<double>& point2) {
    double sum = 0.0;
    for (size_t i = 0; i < point1.size(); ++i) {
        sum += std::pow(point1[i] - point2[i], 2);
    }
    return std::sqrt(sum);
}

// Funzione per assegnare ogni punto al centroide più vicino
std::vector<int> assignPointsToCentroids(const std::vector<std::vector<double>>& points, const std::vector<std::vector<double>>& centroids) {
    std::vector<int> assignments(points.size(), 0);

    for (size_t i = 0; i < points.size(); ++i) {
        double minDistance = std::numeric_limits<double>::max();
        for (size_t j = 0; j < centroids.size(); ++j) {
            double d = distance(points[i], centroids[j]);
            if (d < minDistance) {
                minDistance = d;
                assignments[i] = static_cast<int>(j);
            }
        }
    }

    return assignments;
}

// Funzione per aggiornare i centroidi in base ai punti assegnati
std::vector<std::vector<double>> updateCentroids(const std::vector<std::vector<double>>& points, const std::vector<int>& assignments, int k) {
    std::vector<std::vector<double>> newCentroids(k, std::vector<double>(points[0].size(), 0.0));
    std::vector<int> counts(k, 0);

    for (size_t i = 0; i < points.size(); ++i) {
        int cluster = assignments[i];
        for (size_t j = 0; j < points[i].size(); ++j) {
            newCentroids[cluster][j] += points[i][j];
        }
        counts[cluster]++;
    }

    for (int i = 0; i < k; ++i) {
        for (size_t j = 0; j < newCentroids[i].size(); ++j) {
            newCentroids[i][j] /= counts[i];
        }
    }

    return newCentroids;
}

// Funzione per verificare se i centroidi hanno convergito
bool hasConverged(const std::vector<std::vector<double>>& oldCentroids, const std::vector<std::vector<double>>& newCentroids, double epsilon) {
    for (size_t i = 0; i < oldCentroids.size(); ++i) {
        if (distance(oldCentroids[i], newCentroids[i]) > epsilon) {
            return false;
        }
    }
    return true;
}

// Funzione per eseguire il clustering k-means
std::vector<int> kMeans(const std::vector<std::vector<double>>& points, int k, double epsilon, int maxIterations) {
    // Inizializza i centroidi in modo casuale
    std::vector<std::vector<double>> centroids;
    for (int i = 0; i < k; ++i) {
        centroids.push_back(points[rand() % points.size()]);
    }

    int iterations = 0;
    while (iterations < maxIterations) {
        std::vector<int> assignments = assignPointsToCentroids(points, centroids);

        std::vector<std::vector<double>> newCentroids = updateCentroids(points, assignments, k);

        if (hasConverged(centroids, newCentroids, epsilon)) {
            break;
        }

        centroids = newCentroids;
        iterations++;
    }

    return assignPointsToCentroids(points, centroids);
}

int main() {
    // Esempio di utilizzo
    // Genera alcuni punti dati casuali
    std::vector<std::vector<double>> points = {{1, 2}, {2, 3}, {5, 8}, {7, 8}, {10, 2}, {12, 3}, {15, 8}, {17, 8}};
    
    // Imposta il numero di cluster (k)
    int k = 2;
    
    // Imposta la soglia di convergenza e il numero massimo di iterazioni
    double epsilon = 0.001;
    int maxIterations = 100;
    
    // Perform k-means clustering
    std::vector<int> clusters = kMeans(points, k, epsilon, maxIterations);
    
    // Print the results
    for (size_t i = 0; i < points.size(); ++i) {
        std::cout << "Point " << i << " belongs to cluster " << clusters[i] << std::endl;
    }

    return 0;
}

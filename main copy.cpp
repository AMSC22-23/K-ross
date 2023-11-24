#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

// Function to calculate the Euclidean distance between two points
double distance(const std::vector<double>& point1, const std::vector<double>& point2) {
    double sum = 0.0;
    for (size_t i = 0; i < point1.size(); ++i) {
        sum += std::pow(point1[i] - point2[i], 2);
    }
    return std::sqrt(sum);
}

// Function to assign each point to the nearest centroid
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

// Function to update the centroids based on the assigned points
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

// Function to check if the centroids have converged
bool hasConverged(const std::vector<std::vector<double>>& oldCentroids, const std::vector<std::vector<double>>& newCentroids, double epsilon) {
    for (size_t i = 0; i < oldCentroids.size(); ++i) {
        if (distance(oldCentroids[i], newCentroids[i]) > epsilon) {
            return false;
        }
    }
    return true;
}

// Function to perform k-means clustering
std::vector<int> kMeans(const std::vector<std::vector<double>>& points, int k, double epsilon, int maxIterations) {
    // Initialize centroids randomly
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
    // Example usage
    // Generate some random data points
    std::vector<std::vector<double>> points = {{1, 2}, {2, 3}, {5, 8}, {7, 8}, {10, 2}, {12, 3}, {15, 8}, {17, 8}};
    
    // Set the number of clusters (k)
    int k = 2;
    
    // Set the convergence threshold and maximum number of iterations
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

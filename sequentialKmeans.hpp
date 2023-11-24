
#ifndef SEQUENTIAL_KMEANS_HPP
#define SEQUENTIAL_KMEANS_HPP

#include <vector>

class SequentialKMeans {
public:
    SequentialKMeans(int numClusters);
    void fit(const std::vector<std::vector<double>>& data);
    std::vector<int> predict(const std::vector<std::vector<double>>& data);

private:
    int numClusters;
    std::vector<std::vector<double>> centroids;

    double calculateDistance(const std::vector<double>& point1, const std::vector<double>& point2);
};

#endif // SEQUENTIAL_KMEANS_HPP

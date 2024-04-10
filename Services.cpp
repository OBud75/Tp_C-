#include "Services.h"
#include <algorithm>
#include <climits>

const int INF = INT_MAX;

int getNextNodeToVisit(const std::vector<int>& path, const std::vector<bool>& visited) {
    for (size_t i = 0; i < visited.size(); ++i) {
        if (!visited[i])
            return i;
    }
    return -1;
}


int TSPService::findShortestPath(const std::vector<City>& cities) {
    int n = cities.size();
    std::vector<int> path(n);
    std::vector<bool> visited(n, false);

    path[0] = 0;
    visited[0] = true;

    int current = 0;
    int totalDistance = 0;

    for (int i = 1; i < n; ++i) {
        int nearestNeighbor = getNextNodeToVisit(path, visited);
        int minDistance = INF;

        for (int j = 0; j < n; ++j) {
            if (!visited[j] && cities[current].distances[j] < minDistance) {
                minDistance = cities[current].distances[j];
                nearestNeighbor = j;
            }
        }

        path[i] = nearestNeighbor;
        visited[nearestNeighbor] = true;
        totalDistance += minDistance;
        current = nearestNeighbor;
    }

    totalDistance += cities[current].distances[0];
    return totalDistance;
}

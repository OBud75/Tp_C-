#include "Services.h"
#include <algorithm>
#include <climits>

const int INF = INT_MAX;

// Fonction utilitaire pour trouver le prochain nœud à visiter
int getNextNode(const std::vector<int>& path, const std::vector<bool>& visited) {
    for (size_t i = 0; i < visited.size(); ++i) {
        if (!visited[i])
            return i;
    }
    return -1; // Aucun nœud non visité trouvé
}

// Implémentation de la méthode pour trouver le chemin le plus court
int TSPService::findShortestPath(const std::vector<City>& cities) {
    int n = cities.size();
    std::vector<int> path(n);
    std::vector<bool> visited(n, false);

    path[0] = 0; // Commencer à partir de la première ville
    visited[0] = true;

    int current = 0;
    int totalDistance = 0;

    for (int i = 1; i < n; ++i) {
        int nearestNeighbor = getNextNode(path, visited);
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

    // Ajouter la distance de retour à la ville de départ
    totalDistance += cities[current].distances[0];

    return totalDistance;
}

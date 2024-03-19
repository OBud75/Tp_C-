#ifndef SERVICE_H
#define SERVICE_H

#include "City.h"
#include <vector>

// Classe fournissant des services pour résoudre le problème du voyageur de commerce (TSP)
class TSPService {
public:
    // Méthode pour trouver le chemin le plus court passant par les villes données une seule fois
    static int findShortestPath(const std::vector<City>& cities);
};

#endif // SERVICE_H

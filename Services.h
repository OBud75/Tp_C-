#ifndef SERVICE_H
#define SERVICE_H

#include "City.h"
#include <vector>

// Classe fournissant des services pour r�soudre le probl�me du voyageur de commerce (TSP)
class TSPService {
public:
    // M�thode pour trouver le chemin le plus court passant par les villes donn�es une seule fois
    static int findShortestPath(const std::vector<City>& cities);
};

#endif // SERVICE_H

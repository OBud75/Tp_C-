#ifndef CITY_H
#define CITY_H

#include <vector>
#include <string>

// Structure représentant une ville avec son nom et les distances aux autres villes
struct City {
    char name; // Nom de la ville
    std::vector<int> distances; // Distances de la ville aux autres villes

    // Constructeur par défaut
    City() = default;

    // Constructeur de la ville prenant le nom et les distances en paramètres
    City(char name, const std::vector<int>& distances);
};

#endif // CITY_H

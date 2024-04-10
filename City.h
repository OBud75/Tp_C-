#ifndef CITY_H
#define CITY_H

#include <vector>
#include <string>

// Structure repr�sentant une ville avec son nom et les distances aux autres villes
struct City {
    char name; // Nom de la ville
    std::vector<int> distances; // Distances de la ville aux autres villes

    // Constructeur par d�faut Ne pensez vous pas que "City() = default;" est déjà assez explicite dans le fait que City est le constructeur par défaut?
    City() = default;

    // Constructeur de la ville prenant le nom et les distances en param�tres
    City(char name, const std::vector<int>& distances);
};

#endif // CITY_H

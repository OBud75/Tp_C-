#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm> // Utilisé pour la fonction std::find
#include "City.h"
#include "Services.h"

using namespace std;

// Fonction pour lire les données des villes à partir d'un fichier texte
vector<City> readCitiesFromFile(const string& filename) {
    ifstream file(filename); // Ouvre le fichier
    if (!file.is_open()) { // Vérifie si le fichier est ouvert avec succès
        cerr << "Erreur lors de l'ouverture du fichier." << endl; // Affiche un message d'erreur si le fichier ne peut pas être ouvert
        exit(EXIT_FAILURE); // Termine le programme avec un code d'erreur
    }

    vector<City> cities; // Initialise un vecteur pour stocker les villes lues à partir du fichier
    string line; // Variable pour stocker chaque ligne lue du fichier
    while (getline(file, line)) { // Parcours chaque ligne du fichier
        stringstream ss(line); // Utilise un stringstream pour traiter chaque ligne
        char name; // Variable pour stocker le nom de la ville
        ss >> name; // Lit le nom de la ville à partir du stringstream
        vector<int> distances; // Initialise un vecteur pour stocker les distances de la ville aux autres villes
        int distance; // Variable pour stocker chaque distance
        while (ss >> distance) { // Parcours chaque distance de la ville aux autres villes
            distances.push_back(distance); // Ajoute la distance au vecteur des distances
        }
        cities.push_back(City(name, distances)); // Ajoute la ville avec ses distances au vecteur des villes
    }
    file.close(); // Ferme le fichier après lecture
    return cities; // Retourne le vecteur des villes lues
}

// Fonction pour afficher une liste de villes
void displayCities(const vector<City>& cities) {
    cout << "Liste des villes disponibles :" << endl; // Affiche un en-tête pour la liste des villes
    for (size_t i = 0; i < cities.size(); ++i) { // Parcours chaque ville dans le vecteur
        cout << i + 1 << ". " << cities[i].name << endl; // Affiche le numéro et le nom de la ville
    }
}

// Fonction pour permettre à l'utilisateur de choisir les villes
vector<City> selectCities(const vector<City>& cities) {
    vector<City> selectedCities; // Initialise un vecteur pour stocker les villes sélectionnées par l'utilisateur
    vector<int> chosenIndices; // Initialise un vecteur pour stocker les indices des villes déjà choisies

    displayCities(cities); // Affiche la liste des villes disponibles

    cout << "Choisissez les villes en entrant leurs numéros, terminer en saisissant 0 : " << endl;
    // Demande à l'utilisateur de choisir les villes et de terminer en saisissant 0

    while (true) { // Boucle jusqu'à ce que l'utilisateur termine la sélection
        int choice; // Variable pour stocker le choix de l'utilisateur
        cin >> choice; // Lit le choix de l'utilisateur depuis l'entrée standard
        if (choice == 0) { // Vérifie si l'utilisateur a saisi 0 pour terminer
            break; // Sort de la boucle si l'utilisateur a terminé la sélection
        }
        if (choice >= 1 && choice <= static_cast<int>(cities.size())) { // Vérifie si le choix de l'utilisateur est valide
            if (find(chosenIndices.begin(), chosenIndices.end(), choice) == chosenIndices.end()) {
                // Vérifie si la ville choisie n'a pas déjà été sélectionnée
                chosenIndices.push_back(choice); // Ajoute l'indice de la ville choisie à la liste des indices choisis
                selectedCities.push_back(cities[choice - 1]); // Ajoute la ville sélectionnée au vecteur des villes sélectionnées
            } else {
                cerr << "Cette ville a déjà été choisie. Veuillez réessayer." << endl; // Affiche un message d'erreur si la ville a déjà été sélectionnée
            }
        } else {
            cerr << "Ville invalide. Veuillez réessayer." << endl; // Affiche un message d'erreur si le choix de l'utilisateur est invalide
        }
    }

    return selectedCities; // Retourne le vecteur des villes sélectionnées par l'utilisateur
}

int main() {
    vector<City> cities = readCitiesFromFile("cities.txt"); // Lit les données des villes à partir du fichier "cities.txt"

    vector<City> selectedCities = selectCities(cities); // Permet à l'utilisateur de choisir les villes à partir des données lues

    // Assure que l'utilisateur a choisi au moins 4 villes
    while (selectedCities.size() < 4) {
        cerr << "Vous devez choisir au moins 4 villes. Veuillez réessayer." << endl; // Affiche un message d'erreur si moins de 4 villes ont été choisies
        selectedCities = selectCities(cities); // Permet à l'utilisateur de choisir les villes à nouveau
    }

    // Sélectionne les 4 premières villes si plus de 4 ont été choisies
    if (selectedCities.size() > 4) {
        selectedCities.resize(4); // Réduit le nombre de villes sélectionnées à 4
    }

    int shortestPath = TSPService::findShortestPath(selectedCities); // Trouve le chemin le plus court passant par les villes sélectionnées

    cout << "La longueur du chemin le plus court entre les villes sélectionnées est : " << shortestPath << endl; // Affiche la longueur du chemin le plus court

    return 0; // Termine le programme avec succès
}

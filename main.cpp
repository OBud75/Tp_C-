#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm> // Utilis� pour la fonction std::find
#include "City.h"
#include "Services.h"

using namespace std;

vector<City> readCitiesFromFile(const string& filename) {
    ifstream file(filename); // Ouvre le fichier
    if (!file.is_open()) { // V�rifie si le fichier est ouvert avec succ�s
        cerr << "Erreur lors de l'ouverture du fichier." << endl; // Affiche un message d'erreur si le fichier ne peut pas �tre ouvert
        exit(EXIT_FAILURE); // Termine le programme avec un code d'erreur
    }

    vector<City> cities; // Initialise un vecteur pour stocker les villes lues � partir du fichier
    string line; // Variable pour stocker chaque ligne lue du fichier
    while (getline(file, line)) { // Parcours chaque ligne du fichier
        stringstream ss(line); // Utilise un stringstream pour traiter chaque ligne
        char name; // Variable pour stocker le nom de la ville
        ss >> name; // Lit le nom de la ville � partir du stringstream
        vector<int> distances; // Initialise un vecteur pour stocker les distances de la ville aux autres villes
        int distance; // Variable pour stocker chaque distance
        while (ss >> distance) { // Parcours chaque distance de la ville aux autres villes
            distances.push_back(distance); // Ajoute la distance au vecteur des distances
        }
        cities.push_back(City(name, distances)); // Ajoute la ville avec ses distances au vecteur des villes
    }
    file.close(); // Ferme le fichier apr�s lecture
    return cities; // Retourne le vecteur des villes lues
}

// Fonction pour afficher une liste de villes
void displayCities(const vector<City>& cities) {
    cout << "Liste des villes disponibles :" << endl; // Affiche un en-t�te pour la liste des villes
    for (size_t i = 0; i < cities.size(); ++i) { // Parcours chaque ville dans le vecteur
        cout << i + 1 << ". " << cities[i].name << endl; // Affiche le num�ro et le nom de la ville
    }
}

// Fonction pour permettre � l'utilisateur de choisir les villes
vector<City> selectCities(const vector<City>& cities) {
    vector<City> selectedCities; // Initialise un vecteur pour stocker les villes s�lectionn�es par l'utilisateur
    vector<int> chosenIndices; // Initialise un vecteur pour stocker les indices des villes d�j� choisies

    displayCities(cities); // Affiche la liste des villes disponibles

    cout << "Choisissez les villes en entrant leurs num�ros, terminer en saisissant 0 : " << endl;
    // Demande � l'utilisateur de choisir les villes et de terminer en saisissant 0

    while (true) { // Boucle jusqu'� ce que l'utilisateur termine la s�lection
        int choice; // Variable pour stocker le choix de l'utilisateur
        cin >> choice; // Lit le choix de l'utilisateur depuis l'entr�e standard
        if (choice == 0) { // V�rifie si l'utilisateur a saisi 0 pour terminer
            break; // Sort de la boucle si l'utilisateur a termin� la s�lection
        }
        if (choice >= 1 && choice <= static_cast<int>(cities.size())) { // V�rifie si le choix de l'utilisateur est valide
            if (find(chosenIndices.begin(), chosenIndices.end(), choice) == chosenIndices.end()) {
                // V�rifie si la ville choisie n'a pas d�j� �t� s�lectionn�e
                chosenIndices.push_back(choice); // Ajoute l'indice de la ville choisie � la liste des indices choisis
                selectedCities.push_back(cities[choice - 1]); // Ajoute la ville s�lectionn�e au vecteur des villes s�lectionn�es
            } else {
                cerr << "Cette ville a d�j� �t� choisie. Veuillez r�essayer." << endl; // Affiche un message d'erreur si la ville a d�j� �t� s�lectionn�e
            }
        } else {
            cerr << "Ville invalide. Veuillez r�essayer." << endl; // Affiche un message d'erreur si le choix de l'utilisateur est invalide
        }
    }

    return selectedCities; // Retourne le vecteur des villes s�lectionn�es par l'utilisateur
}

int main() {
    vector<City> cities = readCitiesFromFile("cities.txt"); // Lit les donn�es des villes � partir du fichier "cities.txt"

    vector<City> selectedCities = selectCities(cities); // Permet � l'utilisateur de choisir les villes � partir des donn�es lues

    // Assure que l'utilisateur a choisi au moins 4 villes
    while (selectedCities.size() < 4) {
        cerr << "Vous devez choisir au moins 4 villes. Veuillez r�essayer." << endl; // Affiche un message d'erreur si moins de 4 villes ont �t� choisies
        selectedCities = selectCities(cities); // Permet � l'utilisateur de choisir les villes � nouveau
    }

    // S�lectionne les 4 premi�res villes si plus de 4 ont �t� choisies
    if (selectedCities.size() > 4) {
        selectedCities.resize(4); // R�duit le nombre de villes s�lectionn�es � 4
    }

    int shortestPath = TSPService::findShortestPath(selectedCities); // Trouve le chemin le plus court passant par les villes s�lectionn�es

    cout << "La longueur du chemin le plus court entre les villes s�lectionn�es est : " << shortestPath << endl; // Affiche la longueur du chemin le plus court

    return 0; // Termine le programme avec succ�s
}

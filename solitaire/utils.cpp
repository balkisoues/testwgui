#include "utils.hpp"         // Inclusion du fichier den-tête correspondant (déclaration de la fonction)
#include <fstream>           // Pour manipuler les fichiers (ifstream)
#include <sstream>           // Pour utiliser les flux de chaînes (istringstream)
#include <iostream>          // Pour afficher des messages si besoin (std::cout, std::cerr)

// Fonction qui lit un fichier de configuration et extrait les paramètres nbBilles et mode
bool lireFichierConfig(const std::string& filename, int& nbBilles, std::string& mode) {
    std::ifstream file(filename);  // Ouvre le fichier en lecture

    if (!file.is_open()) return false; // Si le fichier ne s'ouvre pas, on renvoie false (échec)

    std::string line;
    nbBilles = 15;           // Valeur par défaut si non précisée dans le fichier
    mode = "default";        // Mode par défaut

    // Lecture ligne par ligne du fichier
    while (std::getline(file, line)) {
        std::istringstream iss(line);  // Crée un flux à partir de la ligne
        std::string key, val;

        // Tente de séparer chaque ligne selon le format "clé=valeur"
        if (std::getline(iss, key, '=') && std::getline(iss, val)) {
            // Si la clé est "nb_billes", on convertit la valeur en int
            if (key == "nb_billes") nbBilles = std::stoi(val);
            // Si la clé est "mode", on utilise la chaîne telle quelle
            else if (key == "mode") mode = val;
        }
    }

    return true; // Lecture réussie
}

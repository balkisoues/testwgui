#ifndef UTILS_HPP           // Si UTILS_HPP n'est pas encore défini,
#define UTILS_HPP           // on le définit pour éviter les inclusions multiples (protection d'en-tête)

#include <string>           // Inclusion de la bibliothèque string pour utiliser std::string

// Déclaration de la fonction lireFichierConfig.
// Elle prend en paramètre :
// - le nom du fichier à lire (filename)
// - une référence vers un entier (nbBilles) pour récupérer le nombre de billes
// - une référence vers une chaîne de caractères (mode) pour récupérer le mode de jeu
// Elle retourne true si la lecture a réussi, false sinon.
bool lireFichierConfig(const std::string& filename, int& nbBilles, std::string& mode);

#endif                      // Fin de la protection d'en-tête

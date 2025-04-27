#include "board.hpp"     // Inclusion du fichier d'en-tête contenant la définition de la classe Board
#include <iostream>       // Pour afficher dans la console
#include <cstdlib>        // Pour utiliser rand() et srand()
#include <ctime>          // Pour initialiser srand avec l'heure actuelle

// Constructeur de la classe Board
Board::Board()
{
    // Initialise la grille de jeu à SIZE x SIZE (7x7) avec toutes les cases INVALID au départ
    grid = std::vector<std::vector<int>>(SIZE, std::vector<int>(SIZE, INVALID));

    // On parcourt chaque case pour définir les cases valides (zone en forme de croix centrale)
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            if ((i >= 2 && i <= 4) || (j >= 2 && j <= 4))
                grid[i][j] = EMPTY;  // On rend cette case vide (et donc valide)
}

// Vérifie si une case est bien dans la grille et si elle est utilisable (ni hors limite ni invalide)
bool Board::estCaseValide(int ligne, int colonne) const
{
    return ligne >= 0 && ligne < SIZE &&
           colonne >= 0 && colonne < SIZE &&
           grid[ligne][colonne] != INVALID;
}

// Fonction qui initialise la position des billes sur le tablier
void Board::initialiser(int nbBilles, const std::string& mode)
{
    int placed = 0;  // Nombre de billes déjà placées

    if (mode == "random")
    {
        // Mode placement aléatoire

        std::srand(static_cast<unsigned int>(std::time(nullptr))); // Initialisation de la graine aléatoire
        while (placed < nbBilles)
        {
            int i = rand() % SIZE;   // Choix d'une ligne au hasard
            int j = rand() % SIZE;   // Choix d'une colonne au hasard
            if (grid[i][j] == EMPTY)
            {
                grid[i][j] = MARBLE; // Place une bille sur une case vide
                placed++;            // Incrémente le nombre de billes placées
            }
        }
    }
    else
    {
        // Mode placement par défaut : en remplissant la grille de haut en bas, gauche à droite

        for (int i = 0; i < SIZE && placed < nbBilles; ++i)
        {
            for (int j = 0; j < SIZE && placed < nbBilles; ++j)
            {
                if (grid[i][j] == EMPTY)
                {
                    grid[i][j] = MARBLE;
                    placed++;
                }
            }
        }
    }
}

// Affiche le tablier dans la console
void Board::afficher() const
{
    std::cout << "   ";
    for (int j = 0; j < SIZE; ++j) std::cout << j << " ";  // En-tête des colonnes
    std::cout << "\n";

    for (int i = 0; i < SIZE; ++i)
    {
        std::cout << i << "  ";  // Numéro de la ligne

        for (int j = 0; j < SIZE; ++j)
        {
            // Affiche un caractère selon le type de case :
            switch (grid[i][j])
            {
            case INVALID:
                std::cout << "  ";
                break;  // Case invalide (hors plateau) → vide
            case EMPTY:
                std::cout << ". ";
                break;  // Case vide
            case MARBLE:
                std::cout << "O ";
                break;  // Case avec bille
            }
        }
        std::cout << "\n";  // Retour à la ligne après chaque ligne du plateau
    }
}

// verifier la validité de mouvement

bool Board::mouvementValide(int ligneSource, int colSource, int ligneDest, int colDest) const
{
    if (!estCaseValide(ligneSource, colSource) || !estCaseValide(ligneDest, colDest))
        return false;

    if (grid[ligneSource][colSource] != MARBLE || grid[ligneDest][colDest] != EMPTY)
        return false;

    int dx = ligneDest - ligneSource;
    int dy = colDest - colSource;

    if (std::abs(dx) == 2 && dy == 0)   // saut vertical
    {
        int midLigne = (ligneSource + ligneDest) / 2;
        if (grid[midLigne][colSource] == MARBLE)
            return true;
    }
    else if (std::abs(dy) == 2 && dx == 0)     // saut horizontal
    {
        int midCol = (colSource + colDest) / 2;
        if (grid[ligneSource][midCol] == MARBLE)
            return true;
    }

    return false;
}

// deplacer la bille

bool Board::deplacer(int ligneSource, int colSource, int ligneDest, int colDest)
{
    if (!mouvementValide(ligneSource, colSource, ligneDest, colDest))
        return false;

    int midLigne = (ligneSource + ligneDest) / 2;
    int midCol = (colSource + colDest) / 2;

    grid[ligneSource][colSource] = EMPTY;
    grid[midLigne][midCol] = EMPTY;
    grid[ligneDest][colDest] = MARBLE;

    return true;
}

int Board::getCell(int i, int j) const {
    return grid[i][j];
}

void Board::setCell(int i, int j, int value) {
    if (estCaseValide(i, j) || value == INVALID) { // On accepte aussi INVALID
        grid[i][j] = value;
    }
}


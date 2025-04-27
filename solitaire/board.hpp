
#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <string>

const int SIZE = 7;
const int INVALID = -1;
const int EMPTY = 0;
const int MARBLE = 1;

class Board {
private:
    std::vector<std::vector<int>> grid;

public:
    Board();

    bool estCaseValide(int ligne, int colonne) const;
    void initialiser(int nbBilles, const std::string& mode);
    void afficher() const;
    bool mouvementValide(int ligneSource, int colSource, int ligneDest, int colDest) const; // <-- ici très important
    bool deplacer(int ligneSource, int colSource, int ligneDest, int colDest);
    int getCell(int i, int j) const;
    void setCell(int i, int j, int value);

};

#endif

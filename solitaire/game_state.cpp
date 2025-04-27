#include "game_state.hpp"

// Constructeurs
GameState::GameState() {}

GameState::GameState(const vector<vector<char>>& board) {
    currentBoard = board;
}

// Vérifier si seulement une bille reste
bool GameState::estVictoire() const {
    int compteur = 0;
    for (const auto& ligne : currentBoard) {
        for (char caseActuelle : ligne) {
            if (caseActuelle == 'O') { // 'O' représente une bille
                compteur++;
            }
        }
    }
    return (compteur == 1);
}

// Vérifier s'il n'y a plus de mouvements possibles
bool GameState::estDefaite() const {
    // Parcourir toutes les cases pour voir si un mouvement est possible
    int directions[4][2] = { {0,1}, {1,0}, {0,-1}, {-1,0} }; // droite, bas, gauche, haut

    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            if (currentBoard[i][j] == 'O') {
                for (auto& dir : directions) {
                    int ni = i + dir[0];
                    int nj = j + dir[1];
                    int nni = i + 2 * dir[0];
                    int nnj = j + 2 * dir[1];

                    if (ni >= 0 && ni < 7 && nj >= 0 && nj < 7 && nni >= 0 && nni < 7 && nnj >= 0 && nnj < 7) {
                        if (currentBoard[ni][nj] == 'O' && currentBoard[nni][nnj] == '.') {
                            return false; // Un mouvement est encore possible
                        }
                    }
                }
            }
        }
    }
    return true; // Aucun mouvement possible
}

// Sauvegarder l'état actuel du plateau avant un déplacement
void GameState::sauvegarderEtat() {
    history.push_back(currentBoard);
}

// Revenir à l'état précédent
bool GameState::retourArriere() {
    if (!history.empty()) {
        currentBoard = history.back();
        history.pop_back();
        return true; // Retour arrière réussi
    }
    return false; // Impossible (pile vide)
}

// Setter pour mettre à jour l'état courant
void GameState::setBoard(const vector<vector<char>>& board) {
    currentBoard = board;
}

// Getter pour récupérer l'état courant
vector<vector<char>> GameState::getBoard() const {
    return currentBoard;
}

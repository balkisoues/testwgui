#ifndef GAME_STATE_HPP_INCLUDED
#define GAME_STATE_HPP_INCLUDED

#include <vector>
using namespace std;

class GameState {
private:
    vector<vector<char>> currentBoard;  // L'état actuel du plateau
    vector<vector<vector<char>>> history; // Historique des états précédents (pile d'états)

public:
    GameState();
    GameState(const vector<vector<char>>& board);

    bool estVictoire() const;
    bool estDefaite() const;
    void sauvegarderEtat();
    bool retourArriere();
    void setBoard(const vector<vector<char>>& board);
    vector<vector<char>> getBoard() const;
};


#endif // GAME_STATE_HPP_INCLUDED









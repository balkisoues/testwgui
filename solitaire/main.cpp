#include <SFML/Graphics.hpp>
#include "board.hpp"
#include "utils.hpp"
#include "game_state.hpp"
#include <iostream>

const int CELL_SIZE = 80;
const int BOARD_SIZE = 7;
const int WINDOW_SIZE = CELL_SIZE * BOARD_SIZE;
const sf::Color BACKGROUND_COLOR = sf::Color(30, 30, 30);
const sf::Color PEG_COLOR = sf::Color(200, 50, 50);
const sf::Color EMPTY_COLOR = sf::Color(100, 100, 100);
const sf::Color INVALID_COLOR = sf::Color(50, 50, 50);

void drawBoard(sf::RenderWindow& window, Board& board) {
    sf::CircleShape peg(CELL_SIZE / 3);
    peg.setOrigin(peg.getRadius(), peg.getRadius());

    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            int val = board.getCell(i, j);
            peg.setPosition(j * CELL_SIZE + CELL_SIZE / 2, i * CELL_SIZE + CELL_SIZE / 2);

            if (val == MARBLE) {
                peg.setFillColor(PEG_COLOR);
                window.draw(peg);
            } else if (val == EMPTY) {
                peg.setFillColor(EMPTY_COLOR);
                window.draw(peg);
            } else {
                // Draw invalid spots differently if you want (optional)
                peg.setFillColor(INVALID_COLOR);
                window.draw(peg);
            }
        }
    }
}

sf::Vector2i getBoardCoordinates(sf::Vector2i pixelPos) {
    return { pixelPos.y / CELL_SIZE, pixelPos.x / CELL_SIZE };
}

int main() {
    // Set up window
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "Peg Solitaire");
    window.setFramerateLimit(60);

    // Initialization
    int nbBilles;
    std::string mode;

    std::cout << "Entrez le nombre de billes (max 36): ";
    std::cin >> nbBilles;
    std::cout << "Entrez le mode (default ou random): ";
    std::cin >> mode;

    Board board;
    board.initialiser(nbBilles, mode);

    GameState gameState;
    std::vector<std::vector<char>> boardChar(BOARD_SIZE, std::vector<char>(BOARD_SIZE, ' '));

    for (int i = 0; i < BOARD_SIZE; ++i)
        for (int j = 0; j < BOARD_SIZE; ++j) {
            int val = board.getCell(i, j);
            boardChar[i][j] = (val == MARBLE) ? 'O' : (val == EMPTY) ? '.' : ' ';
        }

    gameState.setBoard(boardChar);

    // Game variables
    sf::Vector2i selectedCell(-1, -1);
    bool running = true;

    // Main game loop
    while (window.isOpen() && running) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::Vector2i boardPos = getBoardCoordinates(mousePos);

                if (selectedCell == sf::Vector2i(-1, -1)) {
                    selectedCell = boardPos; // First click
                } else {
                    int sourceLigne = selectedCell.x;
                    int sourceCol = selectedCell.y;
                    int destLigne = boardPos.x;
                    int destCol = boardPos.y;

                    if (board.mouvementValide(sourceLigne, sourceCol, destLigne, destCol)) {
                        // Save state
                        gameState.sauvegarderEtat();
                        board.deplacer(sourceLigne, sourceCol, destLigne, destCol);

                        // Update GameState
                        std::vector<std::vector<char>> updatedBoard(BOARD_SIZE, std::vector<char>(BOARD_SIZE, ' '));
                        for (int i = 0; i < BOARD_SIZE; ++i)
                            for (int j = 0; j < BOARD_SIZE; ++j) {
                                int val = board.getCell(i, j);
                                updatedBoard[i][j] = (val == MARBLE) ? 'O' : (val == EMPTY) ? '.' : ' ';
                            }
                        gameState.setBoard(updatedBoard);

                        if (gameState.estVictoire()) {
                            std::cout << "Bravo, victoire !\n";
                            running = false;
                        } else if (gameState.estDefaite()) {
                            std::cout << "Plus de mouvements possibles. Défaite.\n";
                            running = false;
                        }
                    } else {
                        std::cout << "Déplacement invalide.\n";
                    }

                    selectedCell = {-1, -1}; // Reset selection
                }
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
                if (event.key.code == sf::Keyboard::U) {
                    if (gameState.retourArriere()) {
                        auto restored = gameState.getBoard();
                        for (int i = 0; i < BOARD_SIZE; ++i)
                            for (int j = 0; j < BOARD_SIZE; ++j) {
                                if (restored[i][j] == 'O') board.setCell(i, j, MARBLE);
                                else if (restored[i][j] == '.') board.setCell(i, j, EMPTY);
                                else board.setCell(i, j, INVALID);
                            }
                        std::cout << "Retour arrière effectué.\n";
                    } else {
                        std::cout << "Aucun coup précédent à annuler.\n";
                    }
                }
            }
        }

        window.clear(BACKGROUND_COLOR);
        drawBoard(window, board);
        window.display();
    }

    std::cout << "Fin du jeu.\n";
    return 0;
}

#include <iostream>
#include "BoardState.h"
#include "AgentHuman.h"
#include "AgentMinimaxABH.h"
#include "AgentMinimaxTT.h"
#include <SFML/Graphics.hpp>
#include <cmath>

// DRAWING CONSTANTS
const int CELL_SIZE = 100;

// COLOR CONSTANTS
const sf::Color CELL_COLOR(12, 22, 79);
const sf::Color BG_COLOR(186, 174, 254);
const sf::Color P1_COLOR(186, 30, 104);
const sf::Color P2_COLOR(254, 198, 60);

int main() {
    AgentHuman player1;
    AgentMinimaxTT player2(false);
    BoardState state;

    // Render Window
    sf::RenderWindow window(sf::VideoMode(BoardState::COLUMNS * CELL_SIZE, BoardState::ROWS * CELL_SIZE), "Connect 4");

    // Create Shapes
    sf::RectangleShape cell(sf::Vector2f(CELL_SIZE - 4, CELL_SIZE - 4));
    cell.setFillColor(CELL_COLOR);

    sf::CircleShape discP1(CELL_SIZE / 2 - 6);
    discP1.setFillColor(P1_COLOR);

    sf::CircleShape discP2(CELL_SIZE / 2 - 6);
    discP2.setFillColor(P2_COLOR);


    bool isCurrentPlayer1 = true;

    while (window.isOpen() && !state.checkWinningState()) {
        // Display Background

        window.clear(BG_COLOR);

        std::vector<std::vector<int>> grid = state.getGrid();

        for (int row = 0; row < BoardState::ROWS; row++) {
            for (int column = 0; column < BoardState::COLUMNS; column++) {
                cell.setPosition(column * CELL_SIZE + 2, row * CELL_SIZE + 2);
                discP1.setPosition(column * CELL_SIZE + 6, row * CELL_SIZE + 6);
                discP2.setPosition(column * CELL_SIZE + 6, row * CELL_SIZE + 6);

                window.draw(cell);                                      // Every cell
                if (grid[row][column] == 1) window.draw(discP1);        // Player 1
                else if (grid[row][column] == 2) window.draw(discP2);   // Player 2
            }
        }

        window.display();

        // Gameplay

        int move;

        if (isCurrentPlayer1) {
            move = player1.playColumn(state, window);
        } else {
            move = player2.playColumn(state);
        }

        if (move != -1) {
            state.playMove(move, isCurrentPlayer1);
            isCurrentPlayer1 = !isCurrentPlayer1;
        }

    }

    isCurrentPlayer1 = !isCurrentPlayer1;
    std::cout << "Player " << (isCurrentPlayer1?"1":"2") << " wins!" << "\n";

    char exit;
    std::cin >> exit;

    window.close();

    return 0;
}
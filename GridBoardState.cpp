//
// Created by DEVNA on 02-10-2023.
//

#include "GridBoardState.h"

GridBoardState::GridBoardState() {
    gridBoard.resize(ROWS, std::vector<int>(COLUMNS, 0));
}

bool GridBoardState::isMoveValid(int move) {
    return gridBoard[0][move] == 0;
}

void GridBoardState::playMove(int move, bool isPlayer1) {
    for (int i = ROWS - 1; i >= 0; i--) {
        if (gridBoard[i][move] == 0) {
            gridBoard[i][move] = isPlayer1 ? 1 : 2;
        }
    }
}

int GridBoardState::checkWinningState() const {
    // Check Horizontal
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS - 3; j++) {
            int player = gridBoard[i][j];
            if (player != 0) {  // Skip empty slots
                if (gridBoard[i][j + 1] == player &&
                    gridBoard[i][j + 2] == player &&
                    gridBoard[i][j + 3] == player) {
                    return player;  // Player wins
                }
            }
        }
    }

    // Check Vertical
    for (int i = 0; i < ROWS - 3; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            int player = gridBoard[i][j];
            if (player != 0) {  // Skip empty slots
                if (gridBoard[i + 1][j] == player &&
                    gridBoard[i + 2][j] == player &&
                    gridBoard[i + 3][j] == player) {
                    return player;  // Player wins
                }
            }
        }
    }

    // Check Diagonal (from bottom-left to top-right)
    for (int i = 3; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS - 3; j++) {
            int player = gridBoard[i][j];
            if (player != 0) {  // Skip empty slots
                if (gridBoard[i - 1][j + 1] == player &&
                    gridBoard[i - 2][j + 2] == player &&
                    gridBoard[i - 3][j + 3] == player) {
                    return player;  // Player wins
                }
            }
        }
    }

    // Check Off-Diagonal (from top-left to bottom-right)
    for (int i = 0; i < ROWS - 3; i++) {
        for (int j = 0; j < COLUMNS - 3; j++) {
            int player = gridBoard[i][j];
            if (player != 0) {  // Skip empty slots
                if (gridBoard[i + 1][j + 1] == player &&
                    gridBoard[i + 2][j + 2] == player &&
                    gridBoard[i + 3][j + 3] == player) {
                    return player;  // Player wins
                }
            }
        }
    }

    return 0;  // No winner yet
}


bool GridBoardState::checkDrawState() const {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            if (gridBoard[i][j] == 0) {
                return false;
            }
        }
    }

    return true;
}
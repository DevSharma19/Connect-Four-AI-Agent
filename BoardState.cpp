//
// Created by DEVNA on 01-08-2023.
//

#include "BoardState.h"
#include <iostream>

BoardState::BoardState() {
    player1Bitboard = 0;
    player2Bitboard = 0;
}

uint64_t BoardState::getKey(bool isPlayer1) {
    if (isPlayer1) {
        return getMask() + player1Bitboard;
    } else {
        return getMask() + player2Bitboard;
    }
}

int BoardState::checkWinningState() const {
    if (isWinningState(player1Bitboard)) return 1;
    if (isWinningState(player2Bitboard)) return 2;
    return 0;
}

void BoardState::playMove(int move, bool isPlayer1) {
    if (isPlayer1 && isMoveValid(move)) {
        player1Bitboard += (getMask() + getBottomMask(move)) & getColumnMask(move);
    } else if (isMoveValid(move)) {
        player2Bitboard += (getMask() + getBottomMask(move)) & getColumnMask(move);
    }
}

void BoardState::playSeriesOfMoves(std::string moves) {
    for(int i = 0; i < moves.size(); i++) {
        int column = moves[i] - '0';
        bool isPlayer1 = i % 2 == 0;
        playMove(column, isPlayer1);
    }
}

bool BoardState::isMoveValid(int move) {
    return (getMask() & getTopMask(move)) == 0;
}

std::vector<std::vector<int>> BoardState::getGrid() const {
    std::vector<std::vector<int>> grid(6, std::vector<int>(7, 0));

    for (int row = 0; row < ROWS; row++) {
        for (int column = 0; column < COLUMNS; column++) {
            int bitIndex = getBitIndex(row,column);

            if (player1Bitboard & (UINT64_C(1) << bitIndex)) {
                grid[row][column] = 1; // Player 1's move
            } else if (player2Bitboard & (UINT64_C(1) << bitIndex)) {
                grid[row][column] = 2; // Player 2's move
            } else {
                grid[row][column] = 0; // Empty cell
            }
        }
    }

    return grid;
}

int BoardState::getBitIndex(int row, int column) {
    return (ROWS - row - 1) + column * 7;
}

uint64_t BoardState::getMask() const {
    return player1Bitboard + player2Bitboard;
}

uint64_t BoardState::getColumnMask(int column) {
    return ((UINT64_C(1) << ROWS) - 1) << getBitIndex(5,column);
}

uint64_t BoardState::getTopMask(int column) {
    return UINT64_C(1) << getBitIndex(0,column);
}

uint64_t BoardState::getBottomMask(int column) {
    return UINT64_C(1) << getBitIndex(5,column);
}

void BoardState::printAsGrid(uint64_t bitmap) {
    for (int row = 0; row < ROWS; row++) {
        for (int column = 0; column < COLUMNS; column++) {
            int bitIndex = getBitIndex(row,column);

            if (bitmap & (UINT64_C(1) << bitIndex)) {
                std::cout << "1";
            } else {
                std::cout << "0";
            }
            std::cout << " ";
        }
        std::cout << "\n";
    }
}

bool BoardState::isWinningState(uint64_t bitmap) {
    // diagonal (right to left)
    if ((bitmap & (bitmap >> 6) & (bitmap >> 12) & (bitmap >> 18)) != 0) return true;

    // diagonal (left to right)
    if ((bitmap & (bitmap >> 8) & (bitmap >> 16) & (bitmap >> 24)) != 0) return true;

    // horizontal
    if ((bitmap & (bitmap >> 7) & (bitmap >> 14) & (bitmap >> 21)) != 0) return true;

    // vertical
    if ((bitmap & (bitmap >> 1) & (bitmap >>  2) & (bitmap >>  3)) != 0) return true;

    // default state
    return false;
}

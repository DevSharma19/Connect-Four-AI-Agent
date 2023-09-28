//
// Created by DEVNA on 01-08-2023.
//

#ifndef CONNECT_4_BOARDSTATE_H
#define CONNECT_4_BOARDSTATE_H

#include <cstdint>
#include <vector>
#include <string>

class BoardState {
private:
    static bool isWinningState(uint64_t bitmap);

    static int getBitIndex(int row, int column);
    static uint64_t getColumnMask(int column);
    static uint64_t getTopMask(int column);
    static uint64_t getBottomMask(int column);
    [[nodiscard]] uint64_t getMask() const;
public:
    static const int ROWS = 6;
    static const int COLUMNS = 7;
    uint64_t player1Bitboard; // Bitboard for Player 1's moves
    uint64_t player2Bitboard; // Bitboard for Player 2's moves

    BoardState();

    uint64_t getKey(bool isPlayer1);

    bool isMoveValid(int move);

    void playMove(int move, bool isPlayer1);
    void playSeriesOfMoves(std::string moves);

    int checkWinningState() const;

    static void printAsGrid(uint64_t bitmap);

    [[nodiscard]] std::vector<std::vector<int>> getGrid() const;
};


#endif //CONNECT_4_BOARDSTATE_H

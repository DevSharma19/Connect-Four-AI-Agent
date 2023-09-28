//
// Created by DEVNA on 26-09-2023.
//

#ifndef CONNECT_4_AGENTMINIMAXTT_H
#define CONNECT_4_AGENTMINIMAXTT_H

#include "BoardState.h"
#include <vector>
#include <unordered_map>


class AgentMinimaxTT {
private:
    static const int ORIGINAL_DEPTH = 10;
    bool isPlayer1;

    std::unordered_map<uint64_t, int> transpositionTable;

    static std::vector<int> getValidMoves(BoardState state);

public:
    explicit AgentMinimaxTT(bool isPlayer1);

    int playColumn(BoardState state);
    int minimax(BoardState state, int depth, int alpha, int beta, bool isCurrentPlayer1);

    static int countWinningStates(uint64_t bitmap);
    static int countBits(uint64_t bitmap);
    static int heuristicEvaluation(BoardState state, int depth);
};


#endif //CONNECT_4_AGENTMINIMAXTT_H

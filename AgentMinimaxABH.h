//
// Created by DEVNA on 09-08-2023.
//

#ifndef CONNECT_4_AGENTMINIMAXABH_H
#define CONNECT_4_AGENTMINIMAXABH_H


#include "BoardState.h"
#include <vector>

class AgentMinimaxABH {
private:
    static const int ORIGINAL_DEPTH = 8;
    bool isPlayer1;

    static std::vector<int> getValidMoves(BoardState state);
public:
    explicit AgentMinimaxABH(bool isPlayer1);

    int playColumn(BoardState state);
    int minimax(BoardState state, int depth, int alpha, int beta, bool isCurrentPlayer1);

    static int countWinningStates(uint64_t bitmap);

    static int countBits(uint64_t bitmap);

    static int heuristicEvaluation(BoardState state, int depth);
};


#endif //CONNECT_4_AGENTMINIMAXABH_H

//
// Created by DEVNA on 03-08-2023.
//

#ifndef CONNECT_4_AGENTMINIMAXBASE_H
#define CONNECT_4_AGENTMINIMAXBASE_H

#include "BoardState.h"
#include <vector>

class AgentMinimaxBase {
private:
    static const int ORIGINAL_DEPTH = 7;
    bool isPlayer1;

    long long* totalComputationPointer;

    int heuristicEvaluation(BoardState state);
    static std::vector<int> getValidMoves(BoardState state);
public:
    explicit AgentMinimaxBase(bool isPlayer1, long long* totalComputationPointer);

    int playColumn(BoardState state);
    int minimax(BoardState state, int depth, bool isMaximizingPlayer);
};


#endif //CONNECT_4_AGENTMINIMAXBASE_H

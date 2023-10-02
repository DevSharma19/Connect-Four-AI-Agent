//
// Created by DEVNA on 05-08-2023.
//

#ifndef CONNECT_4_AGENTMINIMAXAB_H
#define CONNECT_4_AGENTMINIMAXAB_H

#include "BoardState.h"
#include <vector>

class AgentMinimaxAB {
private:
    static const int ORIGINAL_DEPTH = 9;
    bool isPlayer1;

    long long* totalComputationPointer;

    int heuristicEvaluation(BoardState state);
    static std::vector<int> getValidMoves(BoardState state);
public:
    explicit AgentMinimaxAB(bool isPlayer1, long long* totalComputationPointer);

    int playColumn(BoardState state);
    int minimax(BoardState state, int depth, int alpha, int beta, bool isCurrentPlayer1);
};


#endif //CONNECT_4_AGENTMINIMAXAB_H

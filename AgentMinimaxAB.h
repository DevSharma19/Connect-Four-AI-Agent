//
// Created by DEVNA on 05-08-2023.
//

#ifndef CONNECT_4_AGENTMINIMAXAB_H
#define CONNECT_4_AGENTMINIMAXAB_H

#include "BoardState.h"
#include <vector>

class AgentMinimaxAB {
private:
    static const int ORIGINAL_DEPTH = 8;
    bool isPlayer1;

    int heuristicEvaluation(BoardState state) const;
    static std::vector<int> getValidMoves(BoardState state);
public:
    explicit AgentMinimaxAB(bool isPlayer1);

    int playColumn(BoardState state);
    int minimax(BoardState state, int depth, int alpha, int beta, bool isCurrentPlayer1);
};


#endif //CONNECT_4_AGENTMINIMAXAB_H

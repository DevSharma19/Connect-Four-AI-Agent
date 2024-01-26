//
// Created by DEVNA on 03-08-2023.
//

#ifndef CONNECT_4_AGENTMINIMAXBASE_H
#define CONNECT_4_AGENTMINIMAXBASE_H

#include "GridBoardState.h"
#include <vector>
#include <cstdint>
#include <vector>
#include <string>

class AgentMinimaxBase {
private:
    static const int ORIGINAL_DEPTH = 7;
    bool isPlayer1;

    int heuristicEvaluation(GridBoardState state);
    static std::vector<int> getValidMoves(GridBoardState state);
public:
    explicit AgentMinimaxBase(bool isPlayer1);

    int playColumn(GridBoardState state);
    int minimax(GridBoardState state, int depth, bool isMaximizingPlayer);
};


#endif //CONNECT_4_AGENTMINIMAXBASE_H

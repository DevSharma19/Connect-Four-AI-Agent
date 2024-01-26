//
// Created by DEVNA on 03-08-2023.
//

#include "AgentMinimaxBase.h"

AgentMinimaxBase::AgentMinimaxBase(bool isPlayer1) : isPlayer1(isPlayer1) {}

int AgentMinimaxBase::playColumn(GridBoardState state) {
    if (isPlayer1) {
        int bestMove = -1;
        int bestScore = INT_MIN;

        std::vector<int> validMoves = getValidMoves(state);

        for (int move : validMoves) {
            GridBoardState newState = state;
            newState.playMove(move, isPlayer1);

            int score = minimax(newState, ORIGINAL_DEPTH, false);

            if (score > bestScore) {
                bestScore = score;
                bestMove = move;
            }
        }

        if (bestScore == INT_MIN) {
            int randomMoveIndex = rand() % validMoves.size();
            bestMove = validMoves[randomMoveIndex];
        }

        return bestMove;
    } else {
        int bestMove = -1;
        int bestScore = INT_MAX;

        std::vector<int> validMoves = getValidMoves(state);

        for (int move : validMoves) {
            GridBoardState newState = state;
            newState.playMove(move, isPlayer1);

            int score = minimax(newState, ORIGINAL_DEPTH, true);

            if (score < bestScore) {
                bestScore = score;
                bestMove = move;
            }
        }

        if (bestScore == INT_MAX) {
            int randomMoveIndex = rand() % validMoves.size();
            bestMove = validMoves[randomMoveIndex];
        }

        return bestMove;
    }
}

int AgentMinimaxBase::minimax(GridBoardState state, int depth, bool isCurrentPlayer1) {
    if (depth == 0 || state.checkWinningState()) {
        return heuristicEvaluation(state);
    }

    if (isCurrentPlayer1) {
        int bestScore = INT_MIN;

        std::vector<int> validMoves = getValidMoves(state);

        for (int move : validMoves) {
            GridBoardState newState = state;
            newState.playMove(move, isCurrentPlayer1);

            int score = minimax(newState, depth - 1, false);

            bestScore = std::max(bestScore, score);
        }

        return bestScore;
    } else {
        int bestScore = INT_MAX;

        std::vector<int> validMoves = getValidMoves(state);

        for (int move : validMoves) {
            GridBoardState newState = state;
            newState.playMove(move, isCurrentPlayer1);

            int score = minimax(newState, depth - 1, true);

            bestScore = std::min(bestScore, score);
        }

        return bestScore;
    }
}

std::vector<int> AgentMinimaxBase::getValidMoves(GridBoardState state) {
    std::vector<int> validMoves;

    for (int column = 0; column < 7; column++) {
        if (state.isMoveValid(column)) {
            validMoves.push_back(column);
        }
    }

    return validMoves;
}

int AgentMinimaxBase::heuristicEvaluation(GridBoardState state) {
    int winningState = state.checkWinningState();

    if (winningState == 1) {
        return INT_MAX;
    } else if (winningState == 2) {
        return INT_MIN;
    } else {
        return 0;
    }
}

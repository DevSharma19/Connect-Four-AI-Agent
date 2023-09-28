//
// Created by DEVNA on 05-08-2023.
//

#include "AgentMinimaxAB.h"

AgentMinimaxAB::AgentMinimaxAB(bool isPlayer1) : isPlayer1(isPlayer1) {}

int AgentMinimaxAB::playColumn(BoardState state) {
    if (isPlayer1) {
        int bestMove = -1;
        int bestScore = INT_MIN;

        std::vector<int> validMoves = getValidMoves(state);

        for (int move : validMoves) {
            BoardState newState = state;
            newState.playMove(move, isPlayer1);

            int score = minimax(newState, ORIGINAL_DEPTH, INT_MIN, INT_MAX, false);

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
            BoardState newState = state;
            newState.playMove(move, isPlayer1);

            int score = minimax(newState, ORIGINAL_DEPTH, INT_MIN, INT_MAX, true);

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

int AgentMinimaxAB::minimax(BoardState state, int depth, int alpha, int beta, bool isCurrentPlayer1) {
    if (depth == 0 || state.checkWinningState()) {
        return heuristicEvaluation(state);
    }

    if (isCurrentPlayer1) {
        int bestScore = INT_MIN;

        std::vector<int> validMoves = getValidMoves(state);

        for (int move : validMoves) {
            BoardState newState = state;
            newState.playMove(move, isCurrentPlayer1);

            int score = minimax(newState, depth - 1, alpha, beta, false);

            bestScore = std::max(bestScore, score);
            alpha = std::max(alpha, bestScore);

            if (beta <= alpha) {
                break; // Beta cut-off
            }
        }

        return bestScore;
    } else {
        int bestScore = INT_MAX;

        std::vector<int> validMoves = getValidMoves(state);

        for (int move : validMoves) {
            BoardState newState = state;
            newState.playMove(move, isCurrentPlayer1);

            int score = minimax(newState, depth - 1, alpha, beta, true);

            bestScore = std::min(bestScore, score);
            beta = std::min(beta, bestScore);

            if (beta <= alpha) {
                break; // Alpha cut-off
            }
        }

        return bestScore;
    }
}

std::vector<int> AgentMinimaxAB::getValidMoves(BoardState state) {
    std::vector<int> validMoves;

    for (int column = 0; column < 7; column++) {
        if (state.isMoveValid(column)) {
            validMoves.push_back(column);
        }
    }

    return validMoves;
}

int AgentMinimaxAB::heuristicEvaluation(BoardState state) const {
    int winningState = state.checkWinningState();

    if (winningState == 1) {
        return INT_MAX;
    } else if (winningState == 2) {
        return INT_MIN;
    } else {
        return 0;
    }
}

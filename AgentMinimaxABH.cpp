//
// Created by DEVNA on 09-08-2023.
//

#include "AgentMinimaxABH.h"

AgentMinimaxABH::AgentMinimaxABH(bool isPlayer1) : isPlayer1(isPlayer1) {}

int AgentMinimaxABH::playColumn(BoardState state) {
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

int AgentMinimaxABH::minimax(BoardState state, int depth, int alpha, int beta, bool isCurrentPlayer1) {
    if (depth == 0 || state.checkWinningState()) {
        return heuristicEvaluation(state, depth);
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

std::vector<int> AgentMinimaxABH::getValidMoves(BoardState state) {
    std::vector<int> validMoves;

    for (int column = 0; column < 7; column++) {
        if (state.isMoveValid(column)) {
            validMoves.push_back(column);
        }
    }

    return validMoves;
}

int AgentMinimaxABH::heuristicEvaluation(BoardState state, int depth) {
    uint64_t columnMask = (UINT64_C(1) << BoardState::ROWS) - 1;
    uint64_t emptyMask = 0;
    for (int i = 0; i < 7; i++) emptyMask += columnMask << (i * 7);

    uint64_t player1PossibilityMask = (~state.player2Bitboard) & emptyMask;
    uint64_t player2PossibilityMask = (~state.player1Bitboard) & emptyMask;

    int winningState = state.checkWinningState();

    if (winningState == 1) {
        return INT_MAX - (ORIGINAL_DEPTH - depth);
    } else if (winningState == 2) {
        return INT_MIN + (ORIGINAL_DEPTH - depth);
    } else {
        return countWinningStates(player1PossibilityMask) - countWinningStates(player2PossibilityMask);
    }
}

int AgentMinimaxABH::countWinningStates(uint64_t bitmap) {
    int winningStates = 0;

    // diagonal (right to left)
    uint64_t diagonalRLBitmap = bitmap & (bitmap >> 6) & (bitmap >> 12) & (bitmap >> 18);
    winningStates += countBits(diagonalRLBitmap);

    // diagonal (left to right)
    uint64_t diagonalLRBitmap = bitmap & (bitmap >> 8) & (bitmap >> 16) & (bitmap >> 24);
    winningStates += countBits(diagonalLRBitmap);

    // horizontal
    uint64_t horizontalBitmap = bitmap & (bitmap >> 7) & (bitmap >> 14) & (bitmap >> 21);
    winningStates += countBits(horizontalBitmap);

    // vertical
    uint64_t verticalBitmap = bitmap & (bitmap >> 1) & (bitmap >>  2) & (bitmap >>  3);
    winningStates += countBits(verticalBitmap);

    return winningStates;
}

int AgentMinimaxABH::countBits(uint64_t bitmap) {
    unsigned int count = 0;

    while (bitmap) {
        count += bitmap & 1;
        bitmap >>= 1;
    }

    return count;
}
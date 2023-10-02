#include <iostream>
#include "BoardState.h"
#include "AgentHuman.h"
#include "AgentMinimaxAB.h"
#include "AgentMinimaxABH.h"
#include "AgentMinimaxTT.h"
#include "AgentMinimaxBase.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>

class Timer {
public:
    Timer(long long* durationPointer) {
        this->durationPointer = durationPointer;
        startTimePoint = std::chrono::high_resolution_clock::now();
    }

    ~Timer() {
        Stop();
    }

    void Stop() {
        endTimePoint = std::chrono::high_resolution_clock::now();

        auto startTime = std::chrono::time_point_cast<std::chrono::microseconds>(startTimePoint).time_since_epoch().count();
        auto endTime = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();

        long long durationValue = (endTime - startTime);
        *durationPointer = durationValue;
    }
private:
    long long* durationPointer;

    std::chrono::time_point<std::chrono::high_resolution_clock> startTimePoint;
    std::chrono::time_point<std::chrono::high_resolution_clock> endTimePoint;
};

int main() {
    // GET DATA
    std::fstream inputFile;
    inputFile.open("C:/Users/DEVNA/Documents/Extended Essay/Data/connect-4-processed.csv");

    // OUTPUT DATA
    std::ofstream outputFile;
    outputFile.open("C:/Users/DEVNA/Documents/Extended Essay/Output Data/minimax-TT-depth-9.csv");
    outputFile << "Counter,Total moves,Total Duration / μs,Average Duration / μs,Total Computation,Average Computation,Winning State (T),Winning State" << std::endl;

    std::string line;

    std::string theoreticalWinningState;
    uint64_t player1Bitboard(0), player2Bitboard(0);

    int counter = 1;

    while (std::getline(inputFile, line) && counter <= 100) {
        std::istringstream ss(line);
        std::string token;

        // Read gameResult
        if (std::getline(ss, token, ','))
            theoreticalWinningState = token;

        // Read player1Bitboard
        if (std::getline(ss, token, ',')) {
            player1Bitboard = std::stoull(token, nullptr);
        }

        // Read player2Bitboard
        if (std::getline(ss, token, ',')) {
            player2Bitboard = std::stoull(token, nullptr);
        }

        // Data Collection
        long long totalDuration = 0;
        long long totalComputation = 0;
        int totalMoves = 0;

        // PLAY GAME
        AgentMinimaxTT player1(true, &totalComputation);
        AgentMinimaxTT player2(false, &totalComputation);
        BoardState state;

        // Read bitboards into the board state variable
        state.player1Bitboard = player1Bitboard;
        state.player2Bitboard = player2Bitboard;

        bool isCurrentPlayer1 = true;

        // Iterate the game until a win or draw is reached
        while (!state.checkWinningState() && !state.checkDrawState()) {
            long long duration = 0;

            int move;

            if (isCurrentPlayer1) {
                Timer timer(&duration);
                move = player1.playColumn(state);
            } else {
                Timer timer(&duration);
                move = player2.playColumn(state);
            }

            if (move != -1) {
                state.playMove(move, isCurrentPlayer1);
                isCurrentPlayer1 = !isCurrentPlayer1;
            }

            totalMoves++;
            totalDuration += duration;
        }

        int winningState = 0;
        if (!state.checkDrawState()) {
            winningState = state.checkWinningState();
        }

        outputFile << counter << "," << totalMoves << "," << totalDuration << ","
                   << totalDuration / totalMoves << "," << totalComputation << ","
                   << totalComputation / totalMoves << "," << theoreticalWinningState << ","
                   << winningState << std::endl;

        std::cout << counter << std::endl;
        counter++;
    }

    inputFile.close();
    outputFile.close();
}
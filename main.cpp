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
    std::ofstream outputDurationFile;
    outputDurationFile.open("C:/Users/DEVNA/Documents/Extended Essay/Results/Experiment 3/minimax-ab-time-durations-depth-8.csv");
    outputDurationFile << "Counter,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34" << std::endl;

    std::ofstream outputComputationsFile;
    outputComputationsFile.open("C:/Users/DEVNA/Documents/Extended Essay/Results/Experiment 3/minimax-ab-time-computations-depth-8.csv");
    outputComputationsFile << "Counter,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34" << std::endl;

    std::string line;

    std::string theoreticalWinningState;
    uint64_t player1Bitboard(0), player2Bitboard(0);

    int counter = 1;

    while (std::getline(inputFile, line) && counter <= 50) {
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
        std::vector<long long> durations(34, 0);
        std::vector<long long> computations(34, 0);
        long long totalComputation = 0;
        int currentMoves = 0;

        // PLAY GAME
        AgentMinimaxAB player1(true, &totalComputation);
        AgentMinimaxAB player2(false, &totalComputation);
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

            durations[currentMoves] = duration;
            computations[currentMoves] = totalComputation;
            totalComputation = 0;
            currentMoves++;
        }

        outputDurationFile << counter;
        for (auto duration : durations) {
            outputDurationFile << "," << duration;
        }
        outputDurationFile << std::endl;

        outputComputationsFile << counter;
        for (auto computation : computations) {
            outputComputationsFile << "," << computation;
        }
        outputComputationsFile << std::endl;

        std::cout << counter << std::endl;
        counter++;
    }

    inputFile.close();
    outputDurationFile.close();
    outputComputationsFile.close();
}
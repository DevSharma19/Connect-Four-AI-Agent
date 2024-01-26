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

int main() {
    // GET DATA
    std::fstream inputFile;
    inputFile.open("C:/Users/DEVNA/Documents/Extended Essay/Data/connect-4-processed.csv");

    // GET OUTPUT FILE
    std::ofstream outputFile;
    outputFile.open("C:/Users/DEVNA/Documents/Extended Essay/Results/Experiment 1/grid-memory-usage.csv");

    std::string line;

    uint64_t player1Bitboard(0), player2Bitboard(0);

    int counter = 1;

    while (std::getline(inputFile, line) && counter <= 50) {
        std::istringstream ss(line);
        std::string token;

        // Discard gameResult
        std::getline(ss, token, ',');

        // Read player1Bitboard
        if (std::getline(ss, token, ',')) {
            player1Bitboard = std::stoull(token, nullptr);
        }

        // Read player2Bitboard
        if (std::getline(ss, token, ',')) {
            player2Bitboard = std::stoull(token, nullptr);
        }

        // Data Collection
        // TODO: Add Memory Consumption

        // PLAY GAME
        AgentMinimaxBase player1(true);
        AgentMinimaxBase player2(false);
        BoardState state;

        // Read bitboards into the board state variable
        state.player1Bitboard = player1Bitboard;
        state.player2Bitboard = player2Bitboard;

        bool isCurrentPlayer1 = true;

        // Iterate the game until a win or draw is reached
        while (!state.checkWinningState() && !state.checkDrawState()) {
            int move;

            if (isCurrentPlayer1) {
                move = player1.playColumn(state);
            } else {
                move = player2.playColumn(state);
            }

            if (move != -1) {
                state.playMove(move, isCurrentPlayer1);
                isCurrentPlayer1 = !isCurrentPlayer1;
            }
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
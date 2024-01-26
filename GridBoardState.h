//
// Created by DEVNA on 02-10-2023.
//

#ifndef CONNECT_4_GRIDBOARDSTATE_H
#define CONNECT_4_GRIDBOARDSTATE_H


#include <vector>

class GridBoardState {
private:
    static const int ROWS = 6;
    static const int COLUMNS = 7;
    std::vector<std::vector<int>> gridBoard;

    int getNextRow(int column);

public:
    GridBoardState();

    bool isMoveValid(int move);

    void playMove(int move, bool isPlayer1);

    int checkWinningState() const;
    bool checkDrawState() const;
};


#endif //CONNECT_4_GRIDBOARDSTATE_H

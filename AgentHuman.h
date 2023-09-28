//
// Created by DEVNA on 03-08-2023.
//

#include <SFML/Graphics.hpp>

#ifndef CONNECT_4_AGENTHUMAN_H
#define CONNECT_4_AGENTHUMAN_H

#include "BoardState.h"

class AgentHuman {
public:
    int playColumn(BoardState state, sf::Window& window);
};


#endif //CONNECT_4_AGENTHUMAN_H

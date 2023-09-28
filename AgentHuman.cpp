//
// Created by DEVNA on 03-08-2023.
//

#include "AgentHuman.h"
#include <iostream>
#include <cmath>

int AgentHuman::playColumn(BoardState state, sf::Window& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::MouseButtonReleased) {
            int mouseX = event.mouseButton.x;
            int move = floor(mouseX / 100);

            if (state.isMoveValid((move))) return move;
        } else {
            break;
        }
    }

    return -1;
}

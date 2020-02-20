#include "pit.h"
#include <iostream>

Pit::Pit() {
    x_pos = -1;
    y_pos = -1;
}

Pit::Pit(int x_pos, int y_pos) {
    this->x_pos = x_pos;
    this->y_pos = y_pos;
}

void Pit::percept() {
    std::cout << "You feel a breeze." << std::endl;
}

void Pit::encounter() {
    std::cout << "You fell into a pit and died." << std::endl;
}
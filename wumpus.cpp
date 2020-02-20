#include "wumpus.h"
#include <iostream>

Wumpus::Wumpus() {
    x_pos = -1;
    y_pos = -1;
}

Wumpus::Wumpus(int x_pos, int y_pos) {
    this->x_pos = x_pos;
    this->y_pos = y_pos;
}

void Wumpus::percept() {
    std::cout << "You smell a terrible stench." << std::endl;
}

void Wumpus::encounter() {
    std::cout << "You encountered the wumpus and were slaughtered by it." << std::endl;
}
#include "wumpus.h"
#include <iostream>

// Wumpus default constructor
Wumpus::Wumpus() {
    x_pos = -1;
    y_pos = -1;
}

// Wumpus normal constructor
Wumpus::Wumpus(int x_pos, int y_pos) {
    this->x_pos = x_pos;
    this->y_pos = y_pos;
}

// Activates when player is in adjacent room to wumpus
void Wumpus::percept() {
    std::cout << "You smell a terrible stench." << std::endl;
}

// Activates when player is in room with wumpus
void Wumpus::encounter() {
    std::cout << "You encountered the wumpus and were slaughtered by it." << std::endl;
}
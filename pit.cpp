#include "pit.h"
#include <iostream>

// Default pit constructor
Pit::Pit() {
    x_pos = -1;
    y_pos = -1;
}

// Normal pit constructor
Pit::Pit(int x_pos, int y_pos) {
    this->x_pos = x_pos;
    this->y_pos = y_pos;
}

// Activates when player is in adjacent room to pit
void Pit::percept() {
    std::cout << "You feel a breeze." << std::endl;
}

// Activates when player is in pit room
void Pit::encounter() {
    std::cout << "You fell into a pit and died." << std::endl;
}
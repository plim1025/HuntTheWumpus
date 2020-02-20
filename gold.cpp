#include "gold.h"
#include <iostream>

// Gold default constructor
Gold::Gold() {
    x_pos = -1;
    y_pos = -1;
}

// Gold normal constructor
Gold::Gold(int x_pos, int y_pos) {
    this->x_pos = x_pos;
    this->y_pos = y_pos;
}

// Activates when player is in adjacent room to gold
void Gold::percept() {
    std::cout << "You see a glimmer nearby." << std::endl;
}

// Activates when player is in gold room
void Gold::encounter() {
    std::cout << "You found the gold!" << std::endl;
}
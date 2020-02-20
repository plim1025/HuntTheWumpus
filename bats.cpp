#include "bats.h"
#include <iostream>

// Bats default constructor
Bats::Bats() {
    x_pos = -1;
    y_pos = -1;
}

// Bats normal constructor
Bats::Bats(int x_pos, int y_pos) {
    this->x_pos = x_pos;
    this->y_pos = y_pos;
}

// Activates when player is in adjacent room to bats
void Bats::percept() {
    std::cout << "You hear wings flapping." << std::endl;
}

// Activates when player is in room with bats
void Bats::encounter() {
    std::cout << "You encountered the super bats and are teleported to a random room." << std::endl;
}
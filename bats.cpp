#include "bats.h"
#include <iostream>

Bats::Bats() {
    x_pos = -1;
    y_pos = -1;
}

Bats::Bats(int x_pos, int y_pos) {
    this->x_pos = x_pos;
    this->y_pos = y_pos;
}

void Bats::percept() {
    std::cout << "You hear wings flapping." << std::endl;
}

void Bats::encounter() {
    std::cout << "You encountered the super bats and are teleported to a random room." << std::endl;
}
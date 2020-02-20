#include "gold.h"
#include <iostream>

Gold::Gold() {
    x_pos = -1;
    y_pos = -1;
}

Gold::Gold(int x_pos, int y_pos) {
    this->x_pos = x_pos;
    this->y_pos = y_pos;
}

void Gold::percept() {
    std::cout << "You see a glimmer nearby." << std::endl;
}

void Gold::encounter() {
    std::cout << "You found the gold!" << std::endl;
}
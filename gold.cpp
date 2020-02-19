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

int Gold::get_x_pos() const {
    return x_pos;
}

int Gold::get_y_pos() const {
    return y_pos;
}

void Gold::set_x_pos(int x_pos) {
    this->x_pos = x_pos;
}

void Gold::set_y_pos(int y_pos) {
    this->y_pos = y_pos;
}

#include "event.h"

int Event::get_x_pos() const {
    return x_pos;
}

int Event::get_y_pos() const {
    return y_pos;
}

void Event::set_x_pos(int x_pos) {
    this->x_pos = x_pos;
}

void Event::set_y_pos(int y_pos) {
    this->y_pos = y_pos;
}


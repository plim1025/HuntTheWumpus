#include "event.h"

// Returns x position of event
int Event::get_x_pos() const {
    return x_pos;
}

// Returns y position of event
int Event::get_y_pos() const {
    return y_pos;
}

// Sets x position of event
void Event::set_x_pos(int x_pos) {
    this->x_pos = x_pos;
}

// Sets y position of event
void Event::set_y_pos(int y_pos) {
    this->y_pos = y_pos;
}


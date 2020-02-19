#include "room.h"
#include "event.h"

Room::Room() {
    event = NULL;
    has_event = false;
    room_char = ' ';
}

Room::Room(Event *event) {
    has_event = true;
    this->event = event;
}

Event* Room::get_event() const {
    return event;
}

bool Room::get_has_event() const {
    return has_event;
}

char Room::get_room_char() const {
    return room_char;
}

void Room::set_event(Event* event) {
    this->event = event;
    has_event = true;
}

void Room::set_room_char(char room_char) {
    this->room_char = room_char;
}
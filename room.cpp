#include "room.h"
#include "event.h"

// Default constructor for room
Room::Room() {
    event = NULL;
    has_event = false;
    room_char = ' ';
}

// Normal constructor for room
Room::Room(Event *event) {
    has_event = true;
    this->event = event;
}

// Returns pointer to event in room
Event* Room::get_event() const {
    return event;
}

// Returns whether room has event or not
bool Room::get_has_event() const {
    return has_event;
}

// Returns stored room character, which relates to event (e.g. 'W' for wumpus)
char Room::get_room_char() const {
    return room_char;
}

// Sets event in room
void Room::set_event(Event* event) {
    this->event = event;
    has_event = true;
}

// Sets room character
void Room::set_room_char(char room_char) {
    this->room_char = room_char;
}
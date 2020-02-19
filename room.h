#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include <vector>
#include "event.h"

class Room {
private:
    Event *event;
    bool has_event;
    char room_char;
public:
    Room();
    Room(Event*);

    Event* get_event() const;
    bool get_has_event() const;
    char get_room_char() const;

    void set_event(Event*);
    void set_room_char(char);
};

#endif
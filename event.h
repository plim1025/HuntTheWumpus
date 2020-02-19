#ifndef EVENT_H
#define EVENT_H

class Event {
public:
    virtual void percept() = 0;
    virtual void encounter() = 0;
};

#endif
#ifndef EVENT_H
#define EVENT_H

class Event {
public:
    virtual void percept() = 0;
    virtual void encounter() = 0;
    virtual int get_x_pos() const = 0;
    virtual int get_y_pos() const = 0;
    virtual void set_x_pos(int) = 0;
    virtual void set_y_pos(int) = 0;
};

#endif
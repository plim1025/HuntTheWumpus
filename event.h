#ifndef EVENT_H
#define EVENT_H

class Event {
protected:
    int x_pos;
    int y_pos;
public:
    virtual void percept() = 0;
    virtual void encounter() = 0;
    int get_x_pos() const;
    int get_y_pos() const;
    void set_x_pos(int);
    void set_y_pos(int);
};

#endif
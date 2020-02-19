#ifndef BATS_H
#define BATS_H

#include "event.h"

class Bats : public Event {
private:
    int x_pos;
    int y_pos;
public:
    Bats();
    Bats(int, int);

    int get_x_pos() const override;
    int get_y_pos() const override;

    void set_x_pos(int) override;
    void set_y_pos(int) override;

    void percept() override;
    void encounter() override;
};

#endif
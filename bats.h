#ifndef BATS_H
#define BATS_H

#include "event.h"

class Bats : public Event {
public:
    Bats();
    Bats(int, int);

    void percept() override;
    void encounter() override;
};

#endif
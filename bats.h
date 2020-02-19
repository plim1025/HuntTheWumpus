#ifndef BATS_H
#define BATS_H

#include "event.h"

class Bats : Event {
public:
    void percept() override;
    void encounter() override;
};

#endif
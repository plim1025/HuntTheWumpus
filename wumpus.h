#ifndef WUMPUS_H
#define WUMPUS_H

#include "event.h"

class Wumpus : Event {
public:
    void percept() override;
    void encounter() override;
};

#endif
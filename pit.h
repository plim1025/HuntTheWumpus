#ifndef PIT_H
#define PIT_H

#include "event.h"

class Pit : Event {
public:
    void percept() override;
    void encounter() override;
};

#endif
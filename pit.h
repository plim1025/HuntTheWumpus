#ifndef PIT_H
#define PIT_H

#include "event.h"

class Pit : public Event {
public:
    Pit();
    Pit(int, int);

    void percept() override;
    void encounter() override;
};

#endif
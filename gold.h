#ifndef GOLD_H
#define GOLD_H

#include "event.h"

class Gold : Event {
public:
    void percept() override;
    void encounter() override;
};

#endif
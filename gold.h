#ifndef GOLD_H
#define GOLD_H

#include "event.h"

class Gold : public Event {
public:
    Gold();
    Gold(int, int);

    void percept() override;
    void encounter() override;
};

#endif
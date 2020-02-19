#include "pit.h"
#include <iostream>

void Pit::percept() {
    std::cout << "You feel a breeze." << std::endl;
}

void Pit::encounter() {
    std::cout << "You fell into a pit and died." << std::endl;
}
#include "gold.h"
#include <iostream>

void Gold::percept() {
    std::cout << "You see a glimmer nearby." << std::endl;
}

void Gold::encounter() {
    std::cout << "You found the gold!" << std::endl;
}
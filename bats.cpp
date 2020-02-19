#include "bats.h"
#include <iostream>

void Bats::percept() {
    std::cout << "You hear wings flapping." << std::endl;
}

void Bats::encounter() {
    std::cout << "You encountered the super bats and are teleported to a random room." << std::endl;
}
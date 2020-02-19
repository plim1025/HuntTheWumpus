#include "wumpus.h"
#include <iostream>

void Wumpus::percept() {
    std::cout << "You smell a terrible stench." << std::endl;
}

void Wumpus::encounter() {
    std::cout << "You encountered the wumpus and were slaughtered by it." << std::endl;
}
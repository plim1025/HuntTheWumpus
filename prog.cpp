#include <iostream>
#include "game.h"
#include "room.h"
#include "event.h"
#include "wumpus.h"
#include "bats.h"
#include "pit.h"
#include "gold.h"

int main() {
    // error handle command line arguments (map size at least 4)
    Game game(30, true);
    std::cout << game << std::endl;
    while(true) {
        game.move_or_fire();
        std::cout << game << std::endl;
    }
    return 0;
}
#include <iostream>
#include "game.h"
#include "room.h"
#include "event.h"
#include "wumpus.h"
#include "bats.h"
#include "pit.h"
#include "gold.h"

int main() {

    Game game(5, true);
    std::cout << game << std::endl;
    game.move_or_fire();
    std::cout << game << std::endl;
    return 0;
}
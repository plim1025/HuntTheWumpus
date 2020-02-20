#include <iostream>
#include "game.h"
#include "room.h"
#include "event.h"
#include "wumpus.h"
#include "bats.h"
#include "pit.h"
#include "gold.h"

int main() {
    // error handle command line arguments (map size at least 3)
    Game game(4, true);
    std::cout << game << std::endl;
    while(!game.game_over()) {
        game.move_or_fire();
        game.room_percept();
        game.room_event();
        std::cout << game << std::endl;
    }
    if(game.won_game())
        std::cout << "You win!" << std::endl;
    else
        std::cout << "You lose!" << std::endl;
    return 0;
}
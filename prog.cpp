#include <iostream>
#include "game.h"
#include "room.h"
#include "event.h"
#include "wumpus.h"
#include "bats.h"
#include "pit.h"
#include "gold.h"

bool handle_command(int, char*, char*);
bool get_debug_mode(char*);

int main(int argc, char**argv) {
    if(!handle_command(argc, argv[1], argv[2])) {
        std::cout << "Run again as [executable] [map size] [bool for debug_mode]" << std::endl;
        return -1;
    }
    Game game(atoi(argv[1]), get_debug_mode(argv[2]));
    while(!game.game_over()) {
        std::cout << game << std::endl;
        game.move_or_fire();
        game.room_percept();
        game.room_event();
    }
    game.print_end_message();
    return 0;
}

bool handle_command(int argc, char* map_size, char* debug_mode) {
    int map_size_int = atoi(map_size);
    std::string debug_mode_string(debug_mode);
    if(argc != 3)
        return false;
    if(atoi(map_size) < 4) {
        std::cout << "Map size must be at least 4" << std::endl;
        return false;
    }
    if(debug_mode_string != "true" && debug_mode_string != "false") {
        std::cout << "Debug mode must be either true or false" << std::endl;
        return false;
    }
    return true;
}

bool get_debug_mode(char* debug_c_str) {
    std::string debug_str(debug_c_str);
    return debug_str == "true" ? true : false;
}
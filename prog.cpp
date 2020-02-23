#include <iostream>
#include <cstdlib>
#include "game.h"
#include "room.h"
#include "event.h"
#include "wumpus.h"
#include "bats.h"
#include "pit.h"
#include "gold.h"

bool handle_command(int, char*, char*);
bool get_debug_mode(char*);
std::string input_play_again();

int main(int argc, char**argv) {
    if(!handle_command(argc, argv[1], argv[2])) {
        std::cout << "Run again as [executable] [map size] [bool for debug_mode]" << std::endl;
        return -1;
    }
    std::string play_again = "1";
    Game game(atoi(argv[1]), get_debug_mode(argv[2]));
    while(play_again == "1" || play_again == "2") {
        while(!game.game_over()) {
            std::cout << game << std::endl;
            game.move_or_fire();
            game.room_percept();
            game.room_event();
        }
        game.print_end_message();
        play_again = input_play_again();
        if(play_again == "2")
            game = Game(atoi(argv[1]), get_debug_mode(argv[2]));
        else
            game.reset_game();
    }
    return 0;
}

// Handles command line arguments - returns true if valid, false otherwise
bool handle_command(int argc, char* map_size, char* debug_mode) {
    if(argc != 3)
        return false;
    int map_size_int = atoi(map_size);
    std::string debug_mode_string(debug_mode);
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

// Converts cstring debug mode into bool
bool get_debug_mode(char* debug_c_str) {
    std::string debug_str(debug_c_str);
    return debug_str == "true" ? true : false;
}

std::string input_play_again() {
    std::string input = "";
    while(input != "1" && input != "2" && input != "3") {
        std::cout << "Enter 1 to play the same map, 2 to play a different map, or 3 to quit the game: ";
        std::getline(std::cin, input);
    }
    return input;
}

#include "game.h"
#include "room.h"
#include "wumpus.h"
#include "bats.h"
#include "pit.h"
#include "gold.h"
#include <iostream>
#include <vector>
#include <cstdlib>

Game::Game() {
    srand(time(NULL));
    map_size = 4;
    debug_mode = false;
    fill_map();
    fill_events();
    wumpus_killed = false;
    gold_taken = false;
    spawn_x = rand() % map_size;
    spawn_y = rand() % map_size;
    x_pos = spawn_x;
    y_pos = spawn_y;
    events[0] = new Wumpus;
    events[1] = new Bats;
    events[2] = new Bats;
    events[3] = new Pit;
    events[4] = new Pit;
    events[5] = new Gold;
    arrows = 3;
    player_alive = true;
}

Game::Game(int map_size, bool debug_mode) {
    srand(time(NULL));
    this->map_size = map_size;
    this->debug_mode = debug_mode;
    for(int i = 0; i < 5; i++) {
        map.push_back(std::vector<Room*>());
        for(int j = 0; j < 5; j++)
            map[i].push_back(new Room());
    }
    fill_events();
    wumpus_killed = false;
    gold_taken = false;
    spawn_x = rand() % map_size;
    spawn_y = rand() % map_size;
    x_pos = spawn_x;
    y_pos = spawn_y;
    events[0] = new Wumpus;
    events[1] = new Bats;
    events[2] = new Bats;
    events[3] = new Pit;
    events[4] = new Pit;
    events[5] = new Gold;
    arrows = 3;
    player_alive = true;
}

Game::~Game() {
    // Delete 2D vector
}

// Prints map
std::ostream& operator<<(std::ostream& stream, const Game& game) {
    int map_size = game.get_map_size();
    for(int i = 0; i < map_size; i++) {
        for(int j = 0; j < map_size; j++)
            stream << "+---";
        stream << "+" << std::endl;
        for(int j = 0; j < 3; j++) {
            for(int k = 0; k < map_size; k++) {
                if(game.get_debug_mode() && j == 0)
                    stream << "| " << game.get_map()[i][k]->get_room_char() << " ";
                else if(j == 1 && k == game.get_x_pos() && i == game.get_y_pos())
                    stream << "| * ";
                else
                    stream << "|   ";
            }
            stream << "|" << std::endl;
        }
    }
    for(int i = 0; i < map_size; i++)
        stream << "+---";
    stream << "+" << std::endl;
    return stream;
}

void Game::fill_map() {
    for(int i = 0; i < 5; i++) {
        map.push_back(std::vector<Room*>());
    for(int j = 0; j < 5; j++)
        map[i].push_back(new Room());
    }
}

// Fills map with all possible events
void Game::fill_events() {
    srand(time(NULL));
    char arr[6] = {'W', 'B', 'B', 'P', 'P', 'G'};
    for(int x = 1; x <= 6; x++) {
        int i = rand() % 4;
        int j = rand() % 4;
        if(map[i][j]->get_has_event())
            x--;
        else {
            map[i][j]->set_event(events[i]);
            map[i][j]->set_room_char(arr[x-1]);
        }
    }
}

void Game::move_or_fire() {
    std::string user_input = "";
    while(user_input != "1" && user_input != "2") {
        std::cout << "Would you like to move (1) or fire an arrow (2)? (You have " << arrows << " arrows left): ";
        std::getline(std::cin, user_input);
    }
    if(user_input == "1")
        move_player();
    // else
        // fire_arrow()
}

void Game::move_player() {
    std::string user_input = "";
    while((user_input != "w" && user_input != "a" && user_input != "s" && user_input != "d") || !valid_move(user_input.c_str()[0])) {
        std::cout << "Move up (w), move left (a), move down (s), move right (d): ";
        std::getline(std::cin, user_input);
    }
    if(user_input == "w")
        y_pos--;
    else if(user_input == "a")
        x_pos--;
    else if(user_input == "s")
        y_pos++;
    else if(user_input == "d")
        x_pos++;
}

bool Game::valid_move(char movement) const {
    if(movement == 'w') {
        if(y_pos - 1 >= 0)
            return true;
    }
    else if(movement == 'a') {
        if(x_pos - 1 >= 0)
            return true;
    }
    else if(movement == 's') {
        if(y_pos + 1 < map_size)
            return true;
    }
    else if(movement == 'd') {
        if(x_pos + 1 < map_size)
            return true;
    }
    std::cout << "This move is not possible. ";
    return false;
}

bool Game::get_debug_mode() const {
    return debug_mode;
}

int Game::get_map_size() const {
    return map_size;
}

int Game::get_x_pos() const {
    return x_pos;
}

int Game::get_y_pos() const {
    return y_pos;
}

std::vector<std::vector<Room*>> Game::get_map() const {
    return map;
}
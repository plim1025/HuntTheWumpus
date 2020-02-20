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
    events[0] = new Wumpus();
    events[1] = new Bats();
    events[2] = new Bats();
    events[3] = new Pit();
    events[4] = new Pit();
    events[5] = new Gold();
    fill_map();
    fill_events();
    wumpus_killed = false;
    gold_taken = false;
    spawn_player();
    x_pos = spawn_x;
    y_pos = spawn_y;
    arrows = 3;
    player_alive = true;
}

Game::Game(int map_size, bool debug_mode) {
    srand(time(NULL));
    this->map_size = map_size;
    this->debug_mode = debug_mode;
    events[0] = new Wumpus();
    events[1] = new Bats();
    events[2] = new Bats();
    events[3] = new Pit();
    events[4] = new Pit();
    events[5] = new Gold();
    fill_map();
    fill_events();
    wumpus_killed = false;
    gold_taken = false;
    spawn_player();
    x_pos = spawn_x;
    y_pos = spawn_y;
    arrows = 3;
    player_alive = true;
}

Game::~Game() {
    // Delete 2D vector
    // delete [] events;
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
                    stream << "| " << game.get_map()[i][k].get_room_char() << " ";
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
    for(int i = 0; i < map_size; i++) {
        map.push_back(std::vector<Room>());
        for(int j = 0; j < map_size; j++)
            map[i].push_back(Room());
    }
}

// Fills map with all possible events
void Game::fill_events() {
    srand(time(NULL));
    char arr[6] = {'W', 'B', 'B', 'P', 'P', 'G'};
    for(int x = 1; x <= 6; x++) {
        int i = rand() % map_size;
        int j = rand() % map_size;
        if(map[i][j].get_has_event())
            x--;
        else {
            map[i][j].set_event(events[x-1]);
            map[i][j].set_room_char(arr[x-1]);
            events[x-1]->set_x_pos(j);
            events[x-1]->set_y_pos(i);
        }
    }
}

void Game::spawn_player() {
    srand(time(NULL));
    int x;
    int y;
    do {
        x = rand() % map_size;
        y = rand() % map_size;
    } while(map[y][x].get_has_event());
    spawn_x = x;
    spawn_y = y;
}

void Game::move_or_fire() {
    std::string input = "";
    while((input != "W" && input != "A" && input != "S" && input != "D" && input != "w" &&
    input != "a" && input != "s" && input != "d" && input != " W" && input != " A" && input != " S" &&
    input != " D" && input != " w" && input != " a" && input != " s" && input != " d") || !valid_move(input.c_str()[0])) {
        std::cout << "Move with WASD. To fire an arrow, you must place a space followed by the direction, indicated with WASD: ";
        std::getline(std::cin, input);
    }
    if(input.c_str()[0] == ' ')
        fire_arrow(input.c_str()[1]);
    else
        move_player(input.c_str()[0]);
}

void Game::move_player(char direction) {
    if(direction == 'w' || direction == 'W')
        y_pos--;
    else if(direction == 'a' || direction == 'A')
        x_pos--;
    else if(direction == 's' || direction == 'S')
        y_pos++;
    else if(direction == 'd' || direction == 'D')
        x_pos++;
}

void Game::fire_arrow(char direction) {
    int wumpus_x = events[0]->get_x_pos();
    int wumpus_y = events[0]->get_y_pos();
    if((direction == 'w' || direction == 'W') && ((wumpus_x == x_pos && wumpus_y == y_pos - 1) || (wumpus_x == x_pos && wumpus_y == y_pos - 2) || (wumpus_x == x_pos && wumpus_y == y_pos - 3))) {
        wumpus_killed = true;
        std::cout << "Wumpus killed" << std::endl;
    } else if((direction == 'a' || direction == 'A') && ((wumpus_x == x_pos - 1 && wumpus_y == y_pos) || (wumpus_x == x_pos - 2 && wumpus_y == y_pos) || (wumpus_x == x_pos - 3 && wumpus_y == y_pos))) {
        wumpus_killed = true;
        std::cout << "Wumpus killed" << std::endl;
    } else if((direction == 's' || direction == 'S') && ((wumpus_x == x_pos && wumpus_y == y_pos + 1) || (wumpus_x == x_pos && wumpus_y == y_pos + 2) || (wumpus_x == x_pos && wumpus_y == y_pos + 3))) {
        wumpus_killed = true;
        std::cout << "Wumpus killed" << std::endl;
    } else if((direction == 'd' || direction == 'D') && ((wumpus_x == x_pos + 1 && wumpus_y == y_pos) || (wumpus_x == x_pos + 2 && wumpus_y == y_pos) || (wumpus_x == x_pos + 3 && wumpus_y == y_pos))) {
        wumpus_killed = true;
        std::cout << "Wumpus killed" << std::endl;
    }
    // else
    // teleport_wumpus();
}

bool Game::valid_move(char direction) const {
    if(direction == 'w' || direction == 'W') {
        if(y_pos - 1 >= 0)
            return true;
    } else if(direction == 'a' || direction == 'A') {
        if(x_pos - 1 >= 0)
            return true;
    } else if(direction == 's' || direction == 'S') {
        if(y_pos + 1 < map_size)
            return true;
    } else if(direction == 'd' || direction == 'D') {
        if(x_pos + 1 < map_size)
            return true;
    } else if(direction == ' ') {
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

std::vector<std::vector<Room>> Game::get_map() const {
    return map;
}
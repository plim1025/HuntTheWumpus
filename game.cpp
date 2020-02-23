#include "game.h"
#include "room.h"
#include "wumpus.h"
#include "bats.h"
#include "pit.h"
#include "gold.h"
#include <iostream>
#include <vector>
#include <cstdlib>

// Game default constructor
Game::Game() {
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
    set_random_room(x_pos, y_pos);
    spawn_x = x_pos;
    spawn_y = y_pos;
    arrows = 3;
    player_alive = true;
}

// Game normal constructor
Game::Game(int map_size, bool debug_mode) {
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
    set_random_room(x_pos, y_pos);
    spawn_x = x_pos;
    spawn_y = y_pos;
    arrows = 3;
    player_alive = true;
}

Game& Game::operator=(const Game& old_game) {
    this->map_size = old_game.map_size;
    this->debug_mode = old_game.debug_mode;
    for(int i = 0; i < 6; i++)
        delete events[i];
    events[0] = new Wumpus();
    events[1] = new Bats();
    events[2] = new Bats();
    events[3] = new Pit();
    events[4] = new Pit();
    events[5] = new Gold();
    map = std::vector<std::vector<Room> >();
    fill_map();
    fill_events();
    wumpus_killed = false;
    gold_taken = false;
    set_random_room(x_pos, y_pos);
    spawn_x = x_pos;
    spawn_y = y_pos;
    arrows = 3;
    player_alive = true;
    return *this;
}

// Game destructor
Game::~Game() {
    for(int i = 0; i < 6; i++)
        delete events[i];
}

// Prints map, accounting for debug mode
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

// Fills map with 2D array of rooms
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

// Sets integer references to random empty room coordinates
void Game::set_random_room(int&x, int&y) {
    srand(time(NULL));
    int rand_x;
    int rand_y;
    do {
        rand_x = rand() % map_size;
        rand_y = rand() % map_size;
    } while(map[rand_y][rand_x].get_has_event());
    x = rand_x;
    y = rand_y;
}

// Asks player to either move or fire arrows and carries out functionality
void Game::move_or_fire() {
    std::string input = "";
    while((input != "W" && input != "A" && input != "S" && input != "D" && input != "w" &&
    input != "a" && input != "s" && input != "d" && input != " W" && input != " A" && input != " S" &&
    input != " D" && input != " w" && input != " a" && input != " s" && input != " d") || !valid_move(input.c_str()[0]) || !valid_shot(input)) {
        std::cout << "Move with WASD. To fire an arrow, you must place a space followed by the direction, indicated with WASD (You have " << arrows << " left): ";
        std::getline(std::cin, input);
    }
    if(input.c_str()[0] == ' ')
        fire_arrow(input.c_str()[1]);
    else
        move_player(input.c_str()[0]);
}

// Moves player specified direction
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

// Fires arrow specified direction
void Game::fire_arrow(char direction) {
    srand(time(NULL));
    arrows--;
    int wumpus_x = events[0]->get_x_pos();
    int wumpus_y = events[0]->get_y_pos();
    if((direction == 'w' || direction == 'W') && ((wumpus_x == x_pos && wumpus_y == y_pos - 1) || (wumpus_x == x_pos && wumpus_y == y_pos - 2) || (wumpus_x == x_pos && wumpus_y == y_pos - 3)))
        kill_wumpus();
    else if((direction == 'a' || direction == 'A') && ((wumpus_x == x_pos - 1 && wumpus_y == y_pos) || (wumpus_x == x_pos - 2 && wumpus_y == y_pos) || (wumpus_x == x_pos - 3 && wumpus_y == y_pos)))
        kill_wumpus();
    else if((direction == 's' || direction == 'S') && ((wumpus_x == x_pos && wumpus_y == y_pos + 1) || (wumpus_x == x_pos && wumpus_y == y_pos + 2) || (wumpus_x == x_pos && wumpus_y == y_pos + 3)))
        kill_wumpus();
    else if((direction == 'd' || direction == 'D') && ((wumpus_x == x_pos + 1 && wumpus_y == y_pos) || (wumpus_x == x_pos + 2 && wumpus_y == y_pos) || (wumpus_x == x_pos + 3 && wumpus_y == y_pos)))
        kill_wumpus();
    // 75% chance wumpus teleports if miss arrow
    else if(rand() % 4 != 0)
        teleport_wumpus();
}

// Resets wumpus room and sets wumpus status to killed
void Game::kill_wumpus() {
    wumpus_killed = true;
    std::cout << "Wumpus killed" << std::endl;
    int wumpus_x = events[0]->get_x_pos();
    int wumpus_y = events[0]->get_y_pos();
    map[wumpus_y][wumpus_x].set_room_char(' ');
}

// Teleports wumpus to random empty room
void Game::teleport_wumpus() {
    // Set old room to have no event
    int wumpus_x = events[0]->get_x_pos();
    int wumpus_y = events[0]->get_y_pos();
    map[wumpus_y][wumpus_x].set_room_char(' ');
    // Set new room to have wumpus event
    int rand_x;
    int rand_y;
    set_random_room(rand_x, rand_y);
    events[0]->set_x_pos(rand_x);
    events[0]->set_y_pos(rand_y);
    map[rand_y][rand_x].set_room_char('W');
}

// Checks if given direction is valid to move - returns true if yes, false otherwise
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

// Checks if enough arrows to fire one
bool Game::valid_shot(std::string input) const {
    // If player did not select to shoot, return true
    if(input.length() < 2)
        return true;
    if(arrows > 0)
        return true;
    else {
        std::cout << "Not enough arrows." << std::endl;
        return false;
    }
}

// Teleports player to random room (not accounting for emptiness)
void Game::teleport_player() {
    srand(time(NULL));
    int rand_x = rand() % map_size;
    int rand_y = rand() % map_size;
    x_pos = rand_x;
    y_pos = rand_y;
    room_percept();
    room_event();
}

// Checks player's current tile for events and performs action based on it
void Game::room_event() {
    char event_char = map[y_pos][x_pos].get_room_char();
    if(event_char == 'W') {
        events[0]->encounter();
        player_alive = false;
    } else if(event_char == 'B') {
        events[1]->encounter();
        teleport_player();
    } else if(event_char == 'P') {
        events[3]->encounter();
        player_alive = false;
    } else if(event_char == 'G') {
        events[5]->encounter();
        int gold_x = events[5]->get_x_pos();
        int gold_y = events[5]->get_y_pos();
        map[gold_y][gold_x].set_room_char(' ');
        gold_taken = true;
    }
}

// Checks player's surrounding tiles (not diagonal) for events and calls their percepts
void Game::room_percept() {
    Room upper = (y_pos + 1 < map_size) ? map[y_pos+1][x_pos] : Room();
    Room lower = (y_pos - 1 >= 0) ? map[y_pos-1][x_pos] : Room();
    Room right = (x_pos + 1 < map_size) ? map[y_pos][x_pos+1] : Room();
    Room left = (x_pos - 1 >= 0) ? map[y_pos][x_pos-1] : Room();
    if(upper.get_room_char() == 'W' || lower.get_room_char() == 'W' || right.get_room_char() == 'W' || left.get_room_char() == 'W')
        events[0]->percept();
    if(upper.get_room_char() == 'B' || lower.get_room_char() == 'B' || right.get_room_char() == 'B' || left.get_room_char() == 'B')
        events[1]->percept();
    if(upper.get_room_char() == 'P' || lower.get_room_char() == 'P' || right.get_room_char() == 'P' || left.get_room_char() == 'P')
        events[3]->percept();
    if(upper.get_room_char() == 'G' || lower.get_room_char() == 'G' || right.get_room_char() == 'G' || left.get_room_char() == 'G')
        events[5]->percept();
}

// Checks if game is over, returns true if yes, false otherwise
bool Game::game_over() {
    // If player dead
    if(!player_alive)
        return true;
    // If player escapes with gold
    else if(gold_taken && x_pos == spawn_x && y_pos == spawn_y)
        return true;
    // If player takes gold and kills wumpus
    else if(gold_taken && wumpus_killed && x_pos == spawn_x && y_pos == spawn_y)
        return true;
    else
        return false;
}

// Prints message when game ends based on what occurred
void Game::print_end_message() {
    // If player escapes with gold
    if(gold_taken && x_pos == spawn_x && y_pos == spawn_y)
        std::cout << "Escaped with the gold, you win." << std::endl;
    // If player takes gold and kills wumpus
    else if(gold_taken && wumpus_killed && x_pos == spawn_x && y_pos == spawn_y)
        std::cout << "Killed the wumpus and collected gold, you win." << std::endl;
    else if(!player_alive)
        std::cout << "You lose." << std::endl;
}

void Game::reset_game() {
    wumpus_killed = false;
    gold_taken = false;
    set_random_room(x_pos, y_pos);
    spawn_x = x_pos;
    spawn_y = y_pos;
    arrows = 3;
    player_alive = true;
}

// Returns whether game is in debug mode or not
bool Game::get_debug_mode() const {
    return debug_mode;
}

// Returns map size as integer
int Game::get_map_size() const {
    return map_size;
}

// Returns x position of player
int Game::get_x_pos() const {
    return x_pos;
}

// Returns y position of player
int Game::get_y_pos() const {
    return y_pos;
}

// Returns entire 2D vector of rooms
std::vector<std::vector<Room> > Game::get_map() const {
    return map;
}

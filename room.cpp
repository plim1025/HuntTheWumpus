#include "room.h"
#include <iostream>
#include <vector>
#include <cstdlib>

#define WUMPUS 1
#define BATS 2
#define PIT 3
#define GOLD 4

Room::Room() {
    map_size = 4;
    map = std::vector<std::vector<char>> (map_size, std::vector<char> (map_size, ' '));
    fill_events();
    debug_mode = true;
}

Room::~Room() {

}

// Prints map
std::ostream& operator<<(std::ostream& stream, const Room& room) {
    int map_size = room.get_map_size();
    for(int i = 0; i < map_size; i++) {
        for(int j = 0; j < map_size; j++)
            stream << "+---";
        stream << "+" << std::endl;
        for(int j = 0; j < 3; j++) {
            for(int k = 0; k < map_size; k++) {
                if(room.get_debug_mode())
                    stream << "| " << room.get_map()[j][k] << " ";
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

void Room::fill_events() {
    srand(time(NULL));
    int arr[4] = {WUMPUS, BATS, PIT, GOLD};
    for(int x = 1; x <= 4; x++) {
        int i = rand() % 4;
        int j = rand() % 4;
        map[i][j] = arr[i];
    }
}

bool Room::get_debug_mode() const {
    return debug_mode;
}

int Room::get_map_size() const {
    return map_size;
}

std::vector<std::vector<char>> Room::get_map() const {
    return map;
}
#include "room.h"
#include <iostream>
#include <vector>
#include <cstdlib>

Room::Room() {
    map_size = 4;
    map = std::vector<std::vector<char>> (map_size, std::vector<char> (map_size, ' '));
    fill_events();
    debug_mode = false;
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
                if(room.get_debug_mode() && j == 0)
                    stream << "| " << room.get_map()[i][k] << " ";
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
    char arr[6] = {'W', 'B', 'B', 'P', 'P', 'G'};
    for(int x = 1; x <= 6; x++) {
        int i = rand() % 4;
        int j = rand() % 4;
        if(map[i][j] != ' ')
            x--;
        else
            map[i][j] = arr[x-1];
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
#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include <vector>
#include "event.h"
#include "wumpus.h"
#include "bats.h"
#include "pit.h"
#include "gold.h"

class Room {
private:
    std::vector<std::vector<char>> map;
    int map_size;
    bool debug_mode;
    bool wumpus_killed;
    bool gold_taken;
    int spawn_x;
    int spawn_y;
    Event *events;
    int x_pos;
    int y_pos;
    int arrows;
    bool player_alive;
public:
    Room();
    Room(int, bool);
    ~Room();

    int get_tile(int, int) const;
    int get_map_size() const;
    std::vector<std::vector<char>> get_map() const;

    bool get_debug_mode() const;

    void fill_events();
    void tile_event();
    void tile_percept();
    void teleport_player();
    void move_wumpus();
    bool game_over();
    bool won_game();
    void move_or_fire();
    void move_player();
    void fire_arrow();
};

std::ostream& operator<<(std::ostream&, const Room& room);

#endif
#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include "room.h"
#include "event.h"
#include "wumpus.h"
#include "bats.h"
#include "pit.h"
#include "gold.h"

class Game {
private:
    int map_size;
    bool debug_mode;
    std::vector<std::vector<Room> > map;
    bool wumpus_killed;
    bool gold_taken;
    int spawn_x;
    int spawn_y;
    Event *events[6];
    int x_pos;
    int y_pos;
    int arrows;
    bool player_alive;
public:
    Game();
    Game(int, bool);
    Game& operator=(const Game&);
    ~Game();

    int get_map_size() const;
    std::vector<std::vector<Room> > get_map() const;
    bool get_debug_mode() const;
    int get_x_pos() const;
    int get_y_pos() const;

    void fill_map();
    void fill_events();
    void room_event();
    void room_percept();
    void set_random_room(int&, int&);
    void teleport_player();
    void teleport_wumpus();
    void kill_wumpus();
    bool game_over();
    void print_end_message();
    void move_or_fire();
    bool valid_move(char) const;
    bool valid_shot(std::string) const;
    void move_player(char);
    void fire_arrow(char);
    void reset_game();
};

std::ostream& operator<<(std::ostream&, const Game& game);

#endif

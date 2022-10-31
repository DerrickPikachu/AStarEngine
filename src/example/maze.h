#pragma once


#include "grid.h"
#include "environment.h"

enum class MazeAction {
    up = 0,
    right = 1,
    down = 2,
    left = 3
};

class Maze : public Environment {
public:
    Maze(int r, int c) :
        horizental_wall_(r + 1, c),
        vertical_wall_(r, c + 1),
        maze_cell_(r, c),
        row_(r),
        col_(c) {}

public:
    std::string to_string();
    void knock_down_wall(int from_r, int from_c, int to_r, int to_c);
    std::vector<MazeAction> get_action();
    void apply_action(MazeAction move);
    std::pair<int, int> next_position(MazeAction move);

public:
    void set_position(int pos_r, int pos_c) {
        current_position_.first = pos_r;
        current_position_.second = pos_c;
    }
    const std::pair<int ,int>& get_position() const { return current_position_; }

private:
    bool is_legal_move(MazeAction move);

private:
    Wall horizental_wall_;
    Wall vertical_wall_;
    Cell maze_cell_;
    size_t row_;
    size_t col_;
    std::pair<int, int> current_position_;
};
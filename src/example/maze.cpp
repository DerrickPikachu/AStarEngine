#include <string>
#include <iostream>
#include <sstream>
#include <assert.h>

#include "maze.h"


std::string Maze::to_string() {
    std::ostringstream oss;
    for (int r = 0; r < row_ + 1; r++) {
        for (int c = 0; c < col_; c++) {
            std::string wall = (horizental_wall_(r, c) == 1)? "##" : "  ";
            oss << "##" << wall;
        }
        oss << "##" << std::endl;
        if (r < row_) {
            for (int c = 0; c < col_; c++) {
                std::string wall = (vertical_wall_(r, c) == 1)? "##" : "  ";
                oss << wall << "  ";
            }
            oss << "##" << std::endl;
        }
    }
    return oss.str();
}

void Maze::knock_down_wall(int from_r, int from_c, int to_r, int to_c) {
    int r_offset = to_r - from_r;
    int c_offset = to_c - from_c;
    if (abs(r_offset) == 1 && c_offset == 0) {
        int wall_r = (r_offset > 0)? to_r : from_r;
        int wall_c = to_c;
        horizental_wall_.knock_down_wall(wall_r, wall_c);
    } else if(r_offset == 0 && abs(c_offset) == 1) {
        int wall_r = to_r;
        int wall_c = (c_offset > 0)? to_c : from_c;
        vertical_wall_.knock_down_wall(wall_r, wall_c);
    } else {
        assert("cannot knock down wall");
    }
}

std::vector<MazeAction> Maze::get_action() {
    std::vector<MazeAction> moves;
    moves.reserve(4);
    int current_r = current_position_.first;
    int current_c = current_position_.second;
    if (current_r - 1 >= 0) { moves.emplace_back(MazeAction::up); }
    if (current_c + 1 < col_) { moves.emplace_back(MazeAction::right); }
    if (current_r + 1 < row_) { moves.emplace_back(MazeAction::down); }
    if (current_c - 1 >= 0) { moves.emplace_back(MazeAction::left); }
    return moves;
}

void Maze::apply_action(MazeAction move) {
    assert(is_legal_move(move));
    std::pair<int, int> next_pos = next_position(move);
    set_position(next_pos.first, next_pos.second);
}

std::pair<int, int> Maze::next_position(MazeAction move) {
    if (move == MazeAction::up) {
        return {current_position_.first - 1, current_position_.second};
    } else if (move == MazeAction::right) {
        return {current_position_.first, current_position_.second + 1};
    } else if (move == MazeAction::down) {
        return {current_position_.first + 1, current_position_.second};
    } else if (move == MazeAction::left) {
        return {current_position_.first, current_position_.second - 1};
    }
    assert(false);
}

bool Maze::is_legal_move(MazeAction move)
{
    if (move == MazeAction::up) {
        return current_position_.first - 1 >= 0 && horizental_wall_(current_position_.first, current_position_.second);
    } else if (move == MazeAction::right) {
        return current_position_.second + 1 < col_ && vertical_wall_(current_position_.first, current_position_.second + 1);
    } else if (move == MazeAction::down) {
        return current_position_.first + 1 < row_ && horizental_wall_(current_position_.first + 1, current_position_.second);
    } else if (move == MazeAction::left) {
        return current_position_.second - 1 >= 0 && vertical_wall_(current_position_.first, current_position_.second);
    }
    assert("illegal move input");
    return false;
}

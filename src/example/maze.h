#pragma once

#include <string>
#include <memory>
#include <vector>
#include <random>

#include "grid.h"
#include "environment.h"
#include "state.h"

// Need to move to other header file
static std::random_device rd;
static std::default_random_engine random_engine(rd());

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
    static std::unique_ptr<Maze> make_maze(int r, int c);
    std::string to_string();
    void knock_down_wall(int from_r, int from_c, int to_r, int to_c);
    std::vector<MazeAction> get_action();
    void apply_action(MazeAction move);
    std::pair<int, int> next_position(MazeAction move);
    bool is_arrived(int r, int c) { return maze_cell_.is_arrived(r, c); }
    void arrived(int r, int c) { maze_cell_.arrived(r, c); }

public:
    void set_position(int pos_r, int pos_c) {
        current_position_.first = pos_r;
        current_position_.second = pos_c;
    }
    const std::pair<int ,int>& get_position() const { return current_position_; }

private:
    static std::unique_ptr<Maze> dfs_maze_generate(std::unique_ptr<Maze> maze);
    bool is_legal_move(MazeAction move);

private:
    Wall horizental_wall_;
    Wall vertical_wall_;
    Cell maze_cell_;
    size_t row_;
    size_t col_;
    std::pair<int, int> current_position_;
};

class MazeState : public State {
public:
    MazeState() = delete;
    MazeState(std::string state_key) : State(state_key) { decode(state_key); }

public:
    virtual std::string encode() override;
    virtual void decode(std::string) override;

public:
    const int& getRow() const { return row; }
    int getRow() { return row; }
    const int& getCol() const { return col; }
    int getCol() { return col; }

protected:
    int row;
    int col;
};
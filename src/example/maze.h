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

class MazeState : public State {
public:
    // TODO:: need move constructor and move operator
    MazeState() = delete;
    MazeState(const MazeState& other);
    MazeState& operator=(const MazeState& other);

public:
    MazeState(std::string state_key) : State(state_key) { decode(state_key); }
    MazeState(int row, int col) : row_(row), col_(col) { key_ = encode(); }

public:
    virtual std::string encode() override;
    virtual void decode(std::string) override;

public:
    int get_row() const { return row_; }
    int get_row() { return row_; }
    int get_col() const { return col_; }
    int get_col() { return col_; }

protected:
    int row_;
    int col_;
};

class Maze : public Environment {
public:
    Maze(int r, int c) :
        horizental_wall_(r + 1, c),
        vertical_wall_(r, c + 1),
        maze_cell_(r, c),
        row_(r),
        col_(c),
        current_state_(0, 0) {}

public:
    virtual std::shared_ptr<State> build_state(std::string key) override { return std::make_shared<MazeState>(key); }
    virtual std::string to_string() const override;
    virtual std::string to_string(const Path&) const override;

public:
    static std::unique_ptr<Maze> make_maze(int r, int c);
    void knock_down_wall(int from_r, int from_c, int to_r, int to_c);
    std::vector<MazeAction> get_all_direction();
    void apply_action(MazeAction move);
    std::pair<int, int> next_position(MazeAction move);
    bool is_arrived(int r, int c) { return maze_cell_.is_arrived(r, c); }
    void arrived(int r, int c) { maze_cell_.arrived(r, c); }
    bool is_legal_move(MazeAction move);
    void build_graph();
    void clean_wall() { horizental_wall_.clean_wall(); vertical_wall_.clean_wall(); }

public:
    void set_position(int pos_r, int pos_c) {
        current_state_ = MazeState(pos_r, pos_c);
    }
    const std::pair<int ,int> get_position() const { 
        return {current_state_.get_row(), current_state_.get_col()};
    }
    const MazeState& get_state() const { return current_state_; }

private:
    static std::unique_ptr<Maze> dfs_maze_generate(std::unique_ptr<Maze> maze);
    void append_edge_by_actions(std::vector<MazeAction> candidates);

private:
    Wall horizental_wall_;
    Wall vertical_wall_;
    Cell maze_cell_;
    size_t row_;
    size_t col_;
    // std::pair<int, int> current_position_;
    MazeState current_state_;
};

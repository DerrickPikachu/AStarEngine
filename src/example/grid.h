#pragma once

#include <vector>

class Grid {
public:
    Grid() = default;
    ~Grid() = default;
    Grid(const Grid& other);
    Grid(Grid&& other);
    Grid& operator=(const Grid& other);
    Grid& operator=(Grid&& other);

public:
    Grid(int r, int c) : row_(r), col_(c), elements_(r * c, 0) {}
    int operator()(int r, int c) const { return elements_[r * col_ + c]; }
    int& operator()(int r, int c) { return elements_[r * col_ + c]; }
    int get_row() { return row_; }
    const int get_row() const { return row_; }
    int get_col() { return col_; }
    const int get_col() const { return col_; }

protected:
    std::vector<int> elements_;
    int row_;
    int col_;
};

class Wall : public Grid {
public:
    Wall() : Grid() {}
    ~Wall() = default;
    Wall(int r, int c);
    Wall(const Wall& other) : Grid((Grid)other) {}
    Wall(Wall&& other) : Grid(std::move((Grid)other)) {}
    Wall& operator=(const Wall& other) { (Grid)(*this) = (Grid)other; return *this; }
    Wall& operator=(Wall&& other) { (Grid)(*this) = std::move((Grid)other); return *this; }

    void knock_down_wall(int r, int c) { elements_[r * col_ + c] = 0; }
};

class Cell : public Grid {
public:
    Cell() : Grid() {}
    ~Cell() = default;
    Cell(int r, int c) : Grid(r, c) {}
    Cell(const Cell& other) : Grid((Grid)other) {}
    Cell(Cell&& other) : Grid(std::move((Grid)other)) {}
    Cell& operator=(const Cell& other) { (Grid)(*this) = (Grid)other; return *this; }
    Cell& operator=(Cell&& other) { (Grid)(*this) = std::move((Grid)other); return *this; }

    void arrived(int r, int c) { elements_[r * col_ + c] = 1; }
    bool is_arrived(int r, int c) { return elements_[r * col_ + c] != 0;}
};
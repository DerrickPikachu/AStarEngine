#include <iostream>
#include "grid.h"

Grid::Grid(const Grid& other) {
    row_ = other.row_;
    col_ = other.col_;
    elements_.resize(row_ * col_, 0);
    for (int i = 0; i < other.elements_.size(); i++) {
        elements_[i] = other.elements_[i];
    }
}

Grid::Grid(Grid&& other) {
    row_ = other.row_;
    col_ = other.col_;
    elements_ = std::move(other.elements_);
    other.row_ = 0;
    other.col_ = 0;
}

Grid& Grid::operator=(const Grid& other) {
    row_ = other.row_;
    col_ = other.col_;
    elements_.resize(row_ * col_, 0);
    for (int i = 0; i < other.elements_.size(); i++) {
        elements_[i] = other.elements_[i];
    }
    return *this;
}

Grid& Grid::operator=(Grid&& other) {
    if (this == &other) { return *this; }
    row_ = other.row_;
    col_ = other.col_;
    elements_ = std::move(other.elements_);
    other.row_ = 0;
    other.col_ = 0;
    return *this;
}

Wall::Wall(int r, int c) : Grid(r, c) {
    for (int& element : elements_) {
        element = 1;
    }
}
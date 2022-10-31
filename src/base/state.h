#pragma once

#include <string>

class State {
public:
    State() {}
    State(std::string state_key) { key_ = state_key; }

public:
    std::string key() const { return key_; }

public:
    virtual std::string encode() { return ""; }
    virtual void decode(std::string) {}

private:
    std::string key_;
};
#pragma once

#include <string>

class State {
public:
    State() {}
    State(State& other) { key_ = other.key_; }
    State(std::string state_key);

public:
    const std::string& key() const { return key_; }

public:
    virtual std::string encode() { return ""; }
    virtual void decode(std::string) {}

protected:
    std::string key_;
};
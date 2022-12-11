#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include <memory>
#include "state.h"

class Environment {
public:
    void append_edge(std::string, std::string);
    virtual std::string state_transition(std::shared_ptr<State>, int /* action index */);
    virtual std::vector<int> valid_actions(std::shared_ptr<State>);
    virtual float astar_heuristic(std::shared_ptr<State>) { return -1.0; }
    virtual std::shared_ptr<State> build_state(std::string) { return nullptr; }

public:
    void set_start_key(std::string key) { start_key = key; }
    void set_target_key(std::string key) { target_key = key; }
    std::string get_start_key() const { return start_key; }
    std::string get_target_key() const { return target_key; }

protected:
    // key is the node information encoded value which correspoding to an adjacency array
    std::unordered_map<std::string, std::vector<std::string>> edges_;
    std::string start_key;
    std::string target_key;
};
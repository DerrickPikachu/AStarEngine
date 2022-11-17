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

protected:
    // key is the node information encoded value which correspoding to an adjacency array
    std::unordered_map<std::string, std::vector<std::string>> edges_;
};
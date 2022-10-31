#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include "state.h"

class Environment {
public:
    void append_edge(std::string, std::string);
    virtual State* state_transition(State*, int /* action index */);
    virtual std::vector<int> valid_actions(State*);
    virtual float astar_heuristic(State*) { return -1.0; }

protected:
    // key is the node information encoded value which correspoding to an adjacency array
    std::unordered_map<std::string, std::vector<std::string>> edges_;
};
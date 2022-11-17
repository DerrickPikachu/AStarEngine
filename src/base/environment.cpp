#include "environment.h"

void Environment::append_edge(std::string key1, std::string key2) {
    edges_[key1].emplace_back(key2);
}

std::string Environment::state_transition(std::shared_ptr<State> current_state, int action_idx) {
    std::string next_key = edges_[current_state->key()][action_idx];
    return next_key;
    // return new State(next_key);
}

std::vector<int> Environment::valid_actions(std::shared_ptr<State> current_state) {
    std::vector<std::string>& edge = edges_[current_state->key()];
    std::vector<int> idx_array(edge.size(), 0);
    for (int i = 0; i < idx_array.size(); i++) { idx_array[i] = i; }
    return idx_array;
}
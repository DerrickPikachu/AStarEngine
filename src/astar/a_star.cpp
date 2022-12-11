#include "a_star.h"
#include "state.h"
#include <stack>
#include <iostream>


std::string Path::to_string() {
    std::string str;
    for (const std::string& key : key_order_) { str += key + " "; }
    return str;
}


Path AStarEngine::run() {
    std::string start_key = environment_->get_start_key();
    std::string target_key = environment_->get_target_key();
    node_pool_[start_key] = std::make_shared<Candidate>(0, 0, start_key);
    candidate_queue_.push(node_pool_[start_key]);

    while (!candidate_queue_.empty()) {
        std::shared_ptr<Candidate> node = candidate_queue_.pop();
        // std::cerr << node->key << "->";
        visited_key_.insert(node->key);
        if (node->key == target_key) { return build_path(); }
        
        std::shared_ptr<State> node_state = environment_->build_state(node->key);
        std::vector<int> moves = environment_->valid_actions(node_state);
        float next_node_g = node->g_value + 1;
        for (const int& action_id : moves) {
            std::string next_key = environment_->state_transition(node_state, action_id);
            if (visited_key_.count(next_key)) { continue; }
            if (node_pool_.count(next_key)) {
                update_candidate(next_key, node->key, next_node_g);
            } else {
                add_candidate(next_key, node->key, next_node_g);
                candidate_queue_.push(node_pool_[next_key]);
            }
        }
    }

    return Path();
}

Path AStarEngine::build_path() {
    // std::cerr << std::endl;
    Path path;
    std::stack<std::string> backward_path;
    std::string target_key = environment_->get_target_key();
    std::string next_key = node_pool_[target_key]->come_from_key;
    backward_path.push(target_key);
    while (next_key != "") {
        backward_path.push(next_key);
        next_key = node_pool_[next_key]->come_from_key;
    }
    while (!backward_path.empty()) {
        path.append(backward_path.top());
        backward_path.pop();
    }
    return path;
}

void AStarEngine::update_candidate(std::string update_key, std::string from_key, float new_g) {
    if (new_g >= node_pool_[update_key]->g_value) { return; }
    node_pool_[update_key]->g_value = new_g;
    node_pool_[update_key]->come_from_key = from_key;
    candidate_queue_.update(node_pool_[update_key]->index);
}

void AStarEngine::add_candidate(std::string new_key, std::string from_key, float new_g) {
    std::shared_ptr<State> new_node_state = environment_->build_state(new_key);
    float new_h = environment_->astar_heuristic(new_node_state);
    node_pool_[new_key] = std::make_shared<Candidate>(new_g, new_h, new_key);
    node_pool_[new_key]->come_from_key = from_key;
}

#pragma once

#include <memory>
#include <vector>
#include <string>
#include <unordered_set>
#include <queue>
#include "environment.h"


template<class T>
class Heap {
public:
    Heap() = default;

    void push(std::shared_ptr<T> new_obj) {
        new_obj->index = pool_.size();
        pool_.push_back(new_obj);
        up_heapify(pool_.size() - 1);
    }

    std::shared_ptr<T> pop() {
        std::shared_ptr<T> popped = pool_[0];
        this->swap(0, pool_.size() - 1);
        pool_.pop_back();
        down_heapify(0);
        return popped;
    }

    bool empty() { return pool_.empty(); }
    void update(int index) { up_heapify(index); }

protected:
    void up_heapify(int i) {
        int parent = (i - 1) / 2;
        if (i == 0) { return; }
        if (pool_[i]->compare(pool_[parent])) {  // i is better than parent
            this->swap(i, parent);
            up_heapify(parent);
        }
    }

    void down_heapify(int i) {
        int largest = i;
        int left = i * 2 + 1;
        int right = i * 2 + 2;
        if (left < pool_.size() && pool_[left]->compare(pool_[i])) { this->swap(left, i); largest = left; }
        if (right < pool_.size() && pool_[right]->compare(pool_[i])) { this->swap(right, i); largest = right; }
        if (largest != i) { down_heapify(largest); }
    }

    void swap(int i, int j) {
        std::shared_ptr<T> tmp = pool_[i];
        pool_[i] = pool_[j];
        pool_[j] = tmp;
        pool_[i]->index = i;
        pool_[j]->index = j;
    }

protected:
    std::vector<std::shared_ptr<T>> pool_;
};

class AStarEngine {
protected:
    class Candidate {
    public:
        Candidate(float g, float h, std::string k) {
            g_value = g;
            h_value = h;
            key = k;
            index = 0;
            come_from_key = "";
        }

        bool compare(std::shared_ptr<Candidate> other) {
            return g_value + h_value < other->g_value + other->h_value;
        }

        float g_value;
        float h_value;
        std::string key;
        std::string come_from_key;
        int index;
    };

public:
    void setEnvironment(std::shared_ptr<Environment> env) { environment_ = env; }
    Path run();

protected:
    Path build_path();
    void update_candidate(std::string update_key, std::string from_key, float new_g);
    void add_candidate(std::string new_key, std::string from_key, float new_g);

protected:
    std::shared_ptr<Environment> environment_;
    std::unordered_set<std::string> visited_key_;
    Heap<Candidate> candidate_queue_;
    std::unordered_map<std::string, std::shared_ptr<Candidate>> node_pool_;
};
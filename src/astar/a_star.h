#pragma once

#include <memory>
#include <vector>
#include <string>
#include <unordered_set>
#include <queue>
#include "environment.h"


class Path {
public:
    Path() = default;
    void append(std::string key) { key_order_.emplace_back(key); }

protected:
    std::vector<std::string> key_order_;
};


template<class T>
class Heap {
public:
    Heap() = default;

    void push(std::shared_ptr<T> new_obj) {
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
    }

protected:
    std::vector<std::shared_ptr<T>> pool_;
};

class AStarEngine {
protected:
    class Candidate {
    public:
        Candidate(float v, std::string k) {
            a_star_value = v;
            key = k;
        }

        bool compare(std::shared_ptr<Candidate> other) {
            return a_star_value < other->a_star_value
        }

        float a_star_value;
        std::string key;
    };

public:
    void setEnvironment(std::shared_ptr<Environment> env) { environment_ = env; }
    Path run();

protected:
    std::shared_ptr<Environment> environment_;
    std::unordered_set<std::string> visited_key_;
    Heap<Candidate> candidate_queue_;
    std::unordered_map<std::string, std::shared_ptr<Candidate>> node_pool_;
};
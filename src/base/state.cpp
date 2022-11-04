#include "state.h"

State::State(std::string state_key) {
    key_ = state_key;
    decode(key_);
}
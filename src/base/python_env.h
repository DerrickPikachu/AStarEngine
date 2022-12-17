#pragma once

#include <pybind11/pybind11.h>
#include <string>
#include <vector>
#include <memory>
#include "environment.h"
#include "state.h"

class PythonState : public State {
public:
    PythonState(PyObject* state_obj) : py_state_(state_obj) { key_ = encode(); }

    PyObject* get_py_state() { return py_state_; }

public:
    virtual std::string encode() override;
    virtual void decode(std::string) override;

protected:
    PyObject* py_state_;
};

class PythonEnv : public Environment {
public:
    virtual std::string state_transition(std::shared_ptr<State>, int /* action index */) override;
    virtual std::vector<int> valid_actions(std::shared_ptr<State>) override;
    virtual float astar_heuristic(std::shared_ptr<State>) override;
    virtual std::shared_ptr<State> build_state(std::string) override;
    virtual std::string to_string() const override;
    virtual std::string to_string(const Path&) const override; 
    void set_state_class(PyObject* state_class) { py_state_class_ = state_class; }
    void set_py_env(PyObject* py_env) { py_env_ = py_env; }

protected:
    PyObject* py_env_;
    PyObject* py_state_class_;
};

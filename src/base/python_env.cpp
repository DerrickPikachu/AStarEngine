#include <iostream>
#include "python_env.h"

std::string PythonState::encode() {
    PyObject* ret = PyObject_CallMethod(py_state_, "encode", nullptr);
    const char* utf8_string = PyUnicode_AsUTF8(ret);
    std::string key(utf8_string);
    Py_DECREF(ret);
    return key;
}

void PythonState::decode(std::string new_key) {
    key_ = new_key;
    PyObject_CallMethod(py_state_, "decode", "(s)", new_key.c_str());
}

std::string PythonEnv::state_transition(std::shared_ptr<State> state, int action_id) {
    if (py_env_ == nullptr) { std::cerr << "Error: env is nullptr!" << std::endl; }
    PyObject* ret = PyObject_CallMethod(py_env_, "state_transition", 
        "(s,i)", state->key().c_str(), action_id);

    if (ret == nullptr) { std::cerr << "Error: return value is nullptr!" << std::endl; }
    const char* utf8_string = PyUnicode_AsUTF8(ret);
    std::string next_key(utf8_string);
    Py_DECREF(ret);
    return next_key;
}

std::vector<int> PythonEnv::valid_actions(std::shared_ptr<State> state) {
    PyObject* ret = PyObject_CallMethod(py_env_, "valid_actions",
        "(s)", state->key().c_str());
    
    if (ret == nullptr) { std::cerr << "Error: valid actions ret is nullptr!" << std::endl; }
    std::vector<int> actions;
    for (Py_ssize_t i = 0; i < PyTuple_Size(ret); i++) {
        PyObject* item = PyTuple_GetItem(ret, i);
        int action_id = PyLong_AsLong(item);
        actions.emplace_back(action_id);
    }
    Py_DECREF(ret);
    return actions;
}

float PythonEnv::astar_heuristic(std::shared_ptr<State> state) {
    PyObject* ret = PyObject_CallMethod(py_env_, "astar_heuristic",
        "(s)", state->key().c_str());
    
    if (ret == nullptr) { std::cerr << "Error: heuristic ret is nullptr!" << std::endl; }
    if (!PyFloat_Check(ret)) { std::cerr << "Error: heuristic ret is not float!" << std::endl; }
    float value = PyFloat_AsDouble(ret);
    Py_DECREF(ret);
    return value;
}

std::shared_ptr<State> PythonEnv::build_state(std::string key) {
    // return std::make_shared<PythonState>(PyObject_CallObject(py_state_class_, "(s)", key.c_str()));
    return std::make_shared<PythonState>(PyObject_CallFunction(py_state_class_, "(s)", key.c_str()));
}

std::string PythonEnv::to_string() const {
    PyObject* ret = PyObject_CallMethod(py_env_, "to_string", nullptr);
    if (ret == nullptr) { std::cerr << "Error: to string ret is nullptr" << std::endl; }
    const char* utf8_string = PyUnicode_AsUTF8(ret);
    std::string board_str(utf8_string);
    Py_DECREF(ret);
    return board_str;
}

std::string PythonEnv::to_string(const Path& path) const {
    return "";
}

void PythonEnv::set_py_env(PyObject* py_env) {
    py_env_ = py_env;
    PyObject* start_key = PyObject_GetAttr(py_env_, PyUnicode_FromString("start_key"));
    PyObject* target_key = PyObject_GetAttr(py_env_, PyUnicode_FromString("target_key"));
    const char* utf8_string = PyUnicode_AsUTF8(start_key);
    set_start_key(std::string(utf8_string));
    utf8_string = PyUnicode_AsUTF8(target_key);
    set_target_key(utf8_string);
}

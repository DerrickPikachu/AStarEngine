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

std::shared_ptr<State> PythonEnv::build_state(std::string key) {
    // return std::make_shared<PythonState>(PyObject_CallObject(py_state_class_, "(s)", key.c_str()));
    return std::make_shared<PythonState>(PyObject_CallFunction(py_state_class_, "(s)", key.c_str()));
}

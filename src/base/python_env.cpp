#include "python_env.h"


std::shared_ptr<State> PythonEnv::build_state(std::string key) {
    return std::make_shared<PythonState>(PyObject_CallObject(py_state_class_, "(s)", key.c_str()));
}
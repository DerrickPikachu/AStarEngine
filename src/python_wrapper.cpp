#include "pybind11/pybind11.h"
#include <memory>
#include <iostream>
#include "python_try.h"
#include "python_env.h"
#include "a_star.h"

namespace py = pybind11;

PYBIND11_MODULE(astar_engine, m) {
    m.doc() = "test pybind";

    py::class_<PythonTest>(m, "PythonTest")
        .def(py::init<>())
        .def("set_obj", [](PythonTest& self, object& obj) {
            self.set_obj(obj.ptr());
        })
        .def("test_method", &PythonTest::test_method)
        .def("str_method", &PythonTest::str_method)
        .def("set_class", [](PythonTest& self, object& py_class) {
            self.set_class(py_class.ptr());
        })
        .def("gen_obj", &PythonTest::gen_obj);
    
    py::class_<PythonState>(m, "PythonState")
        .def(py::init([](object& obj) {
            return new PythonState(obj.ptr());
        }))
        .def("encode", &PythonState::encode)
        .def("decode", &PythonState::decode);

    py::class_<PythonEnv>(m, "PythonEnv")
        .def(py::init<>())
        .def("set_state_class", [](PythonEnv& self, object& py_class) {
            self.set_state_class(py_class.ptr());
        })
        .def("set_py_env", [](PythonEnv& self, object& py_env) {
            self.set_py_env(py_env.ptr());
        })
        .def("state_transition", [](PythonEnv& self, object& state, int action) {
            std::shared_ptr<State> py_state = std::make_shared<PythonState>(state.ptr());
            std::string next_key = self.state_transition(py_state, action);
            return next_key;
        })
        .def("valid_actions", [](PythonEnv& self, object& state) {
            std::shared_ptr<State> py_state = std::make_shared<PythonState>(state.ptr());
            std::vector<int> actions = self.valid_actions(py_state);
            PyObject* tup = PyTuple_New(actions.size());
            for (int i = 0; i < actions.size(); i++) {
                PyObject* val = PyLong_FromLong(actions[i]);
                PyTuple_SetItem(tup, i, val);
            }
            return handle(tup);
        })
        .def("astar_heuristic", [](PythonEnv& self, object& state) {
            std::shared_ptr<State> py_state = std::make_shared<PythonState>(state.ptr());
            float heuristic_value = self.astar_heuristic(py_state);
            return heuristic_value;
        })
        .def("to_string", [](PythonEnv& self) {
            return self.to_string();
        })
        .def("get_start_key", &PythonEnv::get_start_key)
        .def("get_target_key", &PythonEnv::get_target_key);
    
    py::class_<AStarEngine>(m, "AStarEngine")
        .def(py::init<>())
        .def ("set_environment", [](AStarEngine& self, object& py_env, object& py_state_class) {
            std::shared_ptr<PythonEnv> py_env_wrapper = std::make_shared<PythonEnv>();
            py_env_wrapper->set_py_env(py_env.ptr());
            py_env_wrapper->set_state_class(py_state_class.ptr());
            self.set_environment(py_env_wrapper);
        })
        .def("run", [](AStarEngine& self) {
            Path path = self.run();
            PyObject* py_list = PyList_New(0);
            for (int i = 0; i < path.size(); i++) {
                PyList_Append(py_list, PyUnicode_FromString(path.get(i).c_str()));
            }
            return handle(py_list);
        });
}

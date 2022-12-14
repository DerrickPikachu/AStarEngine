#include "pybind11/pybind11.h"
#include "python_try.h"

namespace py = pybind11;

PYBIND11_MODULE(astar_engine, m) {
    m.doc() = "test pybind";

    py::class_<PythonTest>(m, "PythonTest")
        .def(py::init<>())
        .def("set_obj", [](PythonTest & self, object& obj) {
            self.set_obj(obj.ptr());
        })
        .def("test_method", &PythonTest::test_method)
        .def("str_method", &PythonTest::str_method)
        .def("set_class", [](PythonTest & self, object& py_class) {
            self.set_class(py_class.ptr());
        })
        .def("gen_obj", &PythonTest::gen_obj);
}

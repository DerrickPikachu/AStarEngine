#include "pybind11/pybind11.h"

using namespace pybind11;

class PythonTest {
public:
    void test_func();
    void set_obj(PyObject* obj) { test_obj_ = obj; }
    void test_method();
    void str_method(std::string);
    void set_class(PyObject* py_class) { test_class_ = py_class; }
    void gen_obj();

    PyObject* test_obj_;
    PyObject* test_class_;
};
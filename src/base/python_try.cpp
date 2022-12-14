#include "python_try.h"

void PythonTest::test_func() {
    PyObject* v  = PyLong_FromLong(2000000);
    Py_DECREF(v);
}

void PythonTest::test_method() {
    PyObject_CallMethod(test_obj_, "say_something", "(s)", "you are cool");
}

void PythonTest::str_method(std::string s) {
    PyObject_CallMethod(test_obj_, "say_something", "(s)", s.c_str());
}

void PythonTest::gen_obj() {
    test_obj_ = PyObject_CallObject(test_class_, nullptr);
}
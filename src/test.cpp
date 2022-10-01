#include <gtest/gtest.h>
#include <Python.h>

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}

TEST(HelloTest, PythonTest) {
  PyObject * v = PyLong_FromLong(2000000);
}
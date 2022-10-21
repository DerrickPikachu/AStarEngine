#include <gtest/gtest.h>
#include <Python.h>
#include "environment.h"
#include "state.h"

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

TEST(EnvironmentTest, TransitionTest) {
  Environment test_env;
  test_env.append_edge("1", "2");
  test_env.append_edge("2", "3");
  test_env.append_edge("1", "3");

  State* test_state = new State("1");
  test_state = test_env.state_transition(test_state, 0);
  test_state = test_env.state_transition(test_state, 0);
  EXPECT_EQ(test_state->key(), "3");
}

TEST(EnvironmentTest, ValidActionsTest) {
  Environment test_env;
  test_env.append_edge("1", "2");
  test_env.append_edge("2", "3");
  test_env.append_edge("1", "3");

  State* state_one = new State("1");
  State* state_two = new State("2");
  State* state_three = new State("3");

  EXPECT_EQ(test_env.valid_actions(state_one).size(), 2);
  EXPECT_EQ(test_env.valid_actions(state_two).size(), 1);
  EXPECT_EQ(test_env.valid_actions(state_three).size(), 0);
}

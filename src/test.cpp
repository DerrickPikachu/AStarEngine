#include <gtest/gtest.h>
#include <Python.h>
#include <string>
#include <iostream>
#include <vector>

#include "environment.h"
#include "state.h"
#include "maze.h"

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

TEST(MazeTest, ToStringTest) {
  Maze test_maze(3, 3);

  std::string maze_str = "##############\n##  ##  ##  ##\n##############\n##  ##  ##  ##\n##############\n##  ##  ##  ##\n##############\n";
  EXPECT_EQ(test_maze.to_string(), maze_str);
}

TEST(MazeTest, KnockDownWallTest) {
  Maze test_maze(3, 3);

  test_maze.knock_down_wall(0, 0, 0, 1);
  test_maze.knock_down_wall(1, 1, 0, 1);
  test_maze.knock_down_wall(1, 2, 1, 1);
  test_maze.knock_down_wall(1, 2, 2, 2);

  std::string maze_str = "##############\n##      ##  ##\n######  ######\n##  ##      ##\n##########  ##\n##  ##  ##  ##\n##############\n";
  EXPECT_EQ(test_maze.to_string(), maze_str);
}

TEST(MazeTest, GetActionTest) {
  Maze test_maze(3, 3);

  test_maze.set_position(1, 1);
  std::vector<MazeAction> one_one_actions = test_maze.get_action();
  test_maze.set_position(0, 0);
  std::vector<MazeAction> zero_zero_actions = test_maze.get_action();
  test_maze.set_position(2, 0);
  std::vector<MazeAction> two_zero_actions = test_maze.get_action();

  EXPECT_EQ(one_one_actions.size(), 4);
  EXPECT_EQ(zero_zero_actions.size(), 2);
  EXPECT_EQ(two_zero_actions.size(), 2);
  EXPECT_EQ(zero_zero_actions[0], MazeAction::right);
  EXPECT_EQ(zero_zero_actions[1], MazeAction::down);
  EXPECT_EQ(two_zero_actions[0], MazeAction::up);
  EXPECT_EQ(two_zero_actions[1], MazeAction::right);
}

TEST(MazeTest, ApplyActionTest) {
  Maze test_maze(3, 3);

  test_maze.apply_action(MazeAction::right);
  test_maze.apply_action(MazeAction::down);
  test_maze.apply_action(MazeAction::left);
  test_maze.apply_action(MazeAction::up);
  test_maze.apply_action(MazeAction::down);

  EXPECT_EQ(test_maze.get_position().first, 1);
  EXPECT_EQ(test_maze.get_position().second, 0);
}

TEST(MazeTest, NextPositionTest) {
  Maze test_maze(3, 3);

  std::pair<int, int> position = test_maze.next_position(MazeAction::down);
  EXPECT_EQ(position.first, 1);
  EXPECT_EQ(position.second, 0);
}
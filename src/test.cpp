#include <gtest/gtest.h>
#include <Python.h>
#include <string>
#include <iostream>
#include <vector>
#include <memory>

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

  auto test_state = std::make_shared<State>("1");
  std::string key = test_env.state_transition(test_state, 0);
  test_state = std::make_shared<State>(key);
  key = test_env.state_transition(test_state, 0);
  test_state = std::make_shared<State>(key);
  EXPECT_EQ(test_state->key(), "3");
}

TEST(EnvironmentTest, ValidActionsTest) {
  Environment test_env;
  test_env.append_edge("1", "2");
  test_env.append_edge("2", "3");
  test_env.append_edge("1", "3");

  auto state_one = std::make_shared<State>("1");
  auto state_two = std::make_shared<State>("2");
  auto state_three = std::make_shared<State>("3");

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

TEST(MazeTest, GetAllDirectionTest) {
  Maze test_maze(3, 3);

  test_maze.set_position(1, 1);
  std::vector<MazeAction> one_one_actions = test_maze.get_all_direction();
  test_maze.set_position(0, 0);
  std::vector<MazeAction> zero_zero_actions = test_maze.get_all_direction();
  test_maze.set_position(2, 0);
  std::vector<MazeAction> two_zero_actions = test_maze.get_all_direction();

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
  test_maze.clean_wall();

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

TEST(MazeTest, DFSGenerateMazeTest) {
  std::unique_ptr<Maze> test_maze = Maze::make_maze(10, 15);
  std::cerr << test_maze->to_string() << std::endl;

  std::vector<std::pair<int, int>> pos_test = {{0, 0}, {3, 3}, {2, 5}, {6, 2}};

  for (int i = 0; i < pos_test.size(); i++) {
    std::cerr << "pos: " << pos_test[i].first << " " << pos_test[i].second << std::endl;
    test_maze->set_position(pos_test[i].first, pos_test[i].second);
    auto test_state = std::make_shared<MazeState>(pos_test[i].first, pos_test[i].second);
    std::vector<int> action_idx = test_maze->valid_actions(test_state);
    std::vector<MazeAction> action_set = test_maze->get_all_direction();
    for (int i = action_set.size() - 1; i >= 0; i--) {
      if (!test_maze->is_legal_move(action_set[i])) { action_set.erase(action_set.begin() + i); }
    }
    EXPECT_EQ(action_idx.size(), action_set.size());
    for (int i = 0; i < action_idx.size(); i++) {
      std::string next_key = test_maze->state_transition(test_state, action_idx[i]);
      // cannot use apply action here
      std::pair<int, int> next_pos = test_maze->next_position(action_set[i]);
      MazeState tem_state(next_pos.first, next_pos.second);
      EXPECT_EQ(next_key, tem_state.key());
    }
  }
}

TEST(MazeTest, StateTest) {
  std::string test_key = "2_3";
  MazeState test_state(test_key);
  test_state.decode(test_key);
  EXPECT_EQ(test_state.get_row(), 2);
  EXPECT_EQ(test_state.get_col(), 3);
  EXPECT_EQ(test_state.encode(), test_key);
}

TEST(MazeTest, StateConstructorTest) {
  MazeState test_state(5, 5);
  EXPECT_EQ(test_state.get_row(), 5);
  EXPECT_EQ(test_state.get_col(), 5);
  EXPECT_EQ(test_state.key(), "5_5");
}

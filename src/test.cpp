#include <gtest/gtest.h>
#include <Python.h>
#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include "environment.h"
#include "state.h"
#include "maze.h"
#include "a_star.h"
#include "python_try.h"
#include "python_env.h"

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

TEST(MazeTest, BuildStateTest) {
  std::shared_ptr<Environment> env = std::make_shared<Maze>(3, 3);
  std::shared_ptr<State> state = env->build_state("1_2");
  EXPECT_EQ(state->key(), "1_2");
  EXPECT_EQ(std::static_pointer_cast<MazeState>(state)->get_row(), 1);
  EXPECT_EQ(std::static_pointer_cast<MazeState>(state)->get_col(), 2);
}

class TestClass {
public:
  TestClass(int v) : val(v) {}
  int val;
  int index;
  bool compare(std::shared_ptr<TestClass> other) { return val < other->val; }
};

TEST(HeapTest, ReorderTest) {
  Heap<TestClass> test_heap;
  test_heap.push(std::make_shared<TestClass>(5));
  test_heap.push(std::make_shared<TestClass>(2));
  test_heap.push(std::make_shared<TestClass>(4));
  test_heap.push(std::make_shared<TestClass>(3));
  test_heap.push(std::make_shared<TestClass>(1));
  std::vector<int> answer = {1, 2, 3, 4, 5};
  std::vector<int> heap_answer;

  for (int i = 0; i < 5; i++) {
    int value = test_heap.pop()->val;
    EXPECT_EQ(value, answer[i]);
  }
}

TEST(HeapTest, DynamicPushTest) {
  Heap<TestClass> test_heap;
  test_heap.push(std::make_shared<TestClass>(3));
  test_heap.push(std::make_shared<TestClass>(1));
  EXPECT_EQ(test_heap.pop()->val, 1);
  test_heap.push(std::make_shared<TestClass>(6));
  EXPECT_EQ(test_heap.pop()->val, 3);
  test_heap.push(std::make_shared<TestClass>(4));
  EXPECT_EQ(test_heap.pop()->val, 4);
  EXPECT_EQ(test_heap.pop()->val, 6);
}

TEST(HeapTest, UpdateTest) {
  Heap<TestClass> test_heap;
  std::shared_ptr<TestClass> obj1 = std::make_shared<TestClass>(1);
  std::shared_ptr<TestClass> obj2 = std::make_shared<TestClass>(2);
  std::shared_ptr<TestClass> obj3 = std::make_shared<TestClass>(3);
  test_heap.push(obj3);
  test_heap.push(obj1);
  test_heap.push(obj2);
  EXPECT_EQ(obj1->index, 0);
  EXPECT_EQ(obj2->index, 2);
  EXPECT_EQ(obj3->index, 1);
  obj3->val = 0;
  test_heap.update(obj3->index);
  EXPECT_EQ(obj3->index, 0);
  EXPECT_EQ(obj1->index, 1);
}

TEST(AStarTest, RunTest) {
  std::shared_ptr<Environment> env = Maze::make_maze(10, 15);
  env->set_start_key("0_0");
  env->set_target_key("0_9");
  std::cerr << env->to_string() << std::endl;
  AStarEngine engine;
  engine.set_environment(env);
  Path founded_path = engine.run();
  std::cerr << founded_path.to_string() << std::endl;
  std::cerr << env->to_string(founded_path) << std::endl;
}

TEST(PythonTest, FuncTest) {
  setenv("PYTHONPATH", ".", 1);
  Py_Initialize();
  PythonTest pyt;
  pyt.test_func();
  Py_Finalize();
}

// TEST(PythonTest, CallMethodTest) {
//   // setenv("PYTHONPATH", ".", 1);
//   Py_Initialize();
//   PyObject* module_name = PyUnicode_FromString("my_test");
//   PyObject* mod = PyImport_Import(module_name);
//   EXPECT_NE(mod, nullptr);
//   Py_DECREF(module_name);

//   PyObject* dict = PyModule_GetDict(mod);
//   EXPECT_NE(dict, nullptr);
//   Py_DECREF(mod);

//   PyObject* py_class = PyDict_GetItemString(dict, "MyTest");
//   EXPECT_NE(py_class, nullptr);
//   Py_DECREF(dict);
  
//   EXPECT_TRUE(PyCallable_Check(py_class));
//   PyObject* obj = PyObject_CallObject(py_class, nullptr);
//   Py_DECREF(py_class);
  
//   PyObject_CallMethod(obj, "say_hello", nullptr);
//   PyObject_CallMethod(obj, "say_something", "(s)", "I am cool");
//   PyObject_CallMethod(obj, "add_one", "(s,i)", "You are not cool", 10);
//   Py_DECREF(obj);

//   Py_Finalize();
// }

// TEST(PythonTest, PythonEnvTest) {
//   PythonEnv env;
//   PythonState state(nullptr);
// }

import unittest
import py_env.astar_engine
import py_env.sliding_puzzle

class TestSlidingPuzzleState(unittest.TestCase):
    def test_set_state_class(self):
        env = py_env.astar_engine.PythonEnv()
        env.set_state_class(py_env.sliding_puzzle.SlidingPuzzleState)
    
    def test_decode(self):
        state = py_env.sliding_puzzle.SlidingPuzzleState("2_3;2;1;0")
        self.assertEqual(state.board_size_, 2)
        self.assertEqual(state.board_[0][0], 3)
        self.assertEqual(state.board_[0][1], 2)
        self.assertEqual(state.board_[1][0], 1)
        self.assertEqual(state.board_[1][1], 0)
        self.assertEqual(state.empty_pos_[0], 1)
        self.assertEqual(state.empty_pos_[1], 1)
    
    def test_encode(self):
        test_key = "2_3;2;1;0"
        state = py_env.sliding_puzzle.SlidingPuzzleState(test_key)
        self.assertEqual(state.encode(), test_key)
    
    def test_slide(self):
        test_key = "2_3;2;1;0"
        state = py_env.sliding_puzzle.SlidingPuzzleState(test_key)
        next_key = state.slide(0)
        self.assertEqual(next_key, "2_3;0;1;2")
        self.assertEqual(state.board_size_, 2)
        self.assertEqual(state.board_[0][0], 3)
        self.assertEqual(state.board_[0][1], 2)
        self.assertEqual(state.board_[1][0], 1)
        self.assertEqual(state.board_[1][1], 0)
    
    def test_slide2(self):
        test_key = "3_5;4;6;3;2;8;7;0;1"
        state = py_env.sliding_puzzle.SlidingPuzzleState(test_key)
        next_key = state.slide(1)
        self.assertEqual(next_key, "3_5;4;6;3;2;8;7;1;0")
    
    def test_bind_state_constructor(self):
        test_key = "3_5;4;6;3;2;8;7;0;1"
        state = py_env.sliding_puzzle.SlidingPuzzleState(test_key)
        cpp_state = py_env.astar_engine.PythonState(state)

    def test_bind_state_encode(self):
        test_key = "3_5;4;6;3;2;8;7;0;1"
        state = py_env.sliding_puzzle.SlidingPuzzleState(test_key)
        cpp_state = py_env.astar_engine.PythonState(state)
        self.assertEqual(cpp_state.encode(), test_key)
    
    def test_bind_state_encode2(self):
        test_key = "3_5;4;6;3;2;8;7;0;1"
        state = py_env.sliding_puzzle.SlidingPuzzleState(test_key)
        next_key = state.slide(3)
        next_state = py_env.sliding_puzzle.SlidingPuzzleState(next_key)
        cpp_state = py_env.astar_engine.PythonState(next_state)
        self.assertEqual(cpp_state.encode(), "3_5;4;6;3;2;8;0;7;1")
    
    def test_bind_state_decode(self):
        test_key = "2_3;2;1;0"
        state = py_env.sliding_puzzle.SlidingPuzzleState('')
        cpp_state = py_env.astar_engine.PythonState(state)
        cpp_state.decode(test_key)
        self.assertEqual(cpp_state.encode(), test_key)
    

class TestSlidingPuzzleEnv(unittest.TestCase):
    def test_state_transition(self):
        env = py_env.sliding_puzzle.SlidingPuzzleEnv(2)
        test_key = "2_3;2;1;0"
        next_key = env.state_transition(test_key, 0)
        self.assertEqual(next_key, "2_3;0;1;2")
    
    def test_bind_state_transition(self):
        env = py_env.sliding_puzzle.SlidingPuzzleEnv(2)
        cpp_env = py_env.astar_engine.PythonEnv()
        cpp_env.set_py_env(env)
        test_key = "2_3;2;1;0"
        state = py_env.sliding_puzzle.SlidingPuzzleState(test_key)
        next_key = cpp_env.state_transition(state, 0)
        self.assertEqual(next_key, "2_3;0;1;2")

    def test_valid_actions(self):
        env = py_env.sliding_puzzle.SlidingPuzzleEnv(2)
        test_key = "2_3;2;1;0"
        actions = env.valid_actions(test_key)
        answer = [0, 3]
        self.assertEqual(len(answer), len(actions))
        for i in range(len(answer)):
            self.assertEqual(actions[i], answer[i])
        
    def test_valid_actions2(self):
        env = py_env.sliding_puzzle.SlidingPuzzleEnv(3)
        test_key = "3_5;4;6;3;2;8;7;0;1"
        actions = env.valid_actions(test_key)
        answer = [0, 1, 3]
        self.assertEqual(len(answer), len(actions))
        for i in range(len(answer)):
            self.assertEqual(actions[i], answer[i])
    
    def test_valid_actions3(self):
        env = py_env.sliding_puzzle.SlidingPuzzleEnv(3)
        test_key = "3_0;4;6;3;2;8;7;5;1"
        actions = env.valid_actions(test_key)
        answer = [1, 2]
        self.assertEqual(len(answer), len(actions))
        for i in range(len(answer)):
            self.assertEqual(actions[i], answer[i])
    
    def test_astar_heuristic(self):
        env = py_env.sliding_puzzle.SlidingPuzzleEnv(3)
        test_key = [
            "3_1;2;3;4;5;6;0;7;8",
            "3_0;4;6;7;1;3;2;5;8",
            "3_0;1;3;2;5;6;7;4;8"
        ]
        answer = [2, 12, 6]
        for i in range(len(answer)):
            heuristic_value = env.astar_heuristic(test_key[i])
            self.assertEqual(heuristic_value, answer[i])


if __name__ == "__main__":
    unittest.main()

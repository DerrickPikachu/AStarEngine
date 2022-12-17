from enum import Enum
import random

class SlidingPuzzleAction(Enum):
    UP = 0
    RIGHT = 1
    DOWN = 2
    LEFT = 3

# key format: {board_size}_{pos1 puzzle};{pos2 puzzle};{pos3 puzzle}...;{posn puzzle}
class SlidingPuzzleState:
    def __init__(self, key):
        self.key_ = key
        self.empty_pos_ = [-1, -1]
        self.board_size_ = 0
        self.board_ = []
        if key != '':
            self.decode(key)
    
    def encode(self):
        key = str(self.board_size_) + '_'
        for i in range(self.board_size_ * self.board_size_):
            key += f'{self.board_[i // self.board_size_][i % self.board_size_]};'
        return key[:-1]

    def decode(self, key):
        terms = key.split('_')
        if self.board_size_ == 0:
            self.board_size_ = int(terms[0])
            self.board_ = [[0 for i in range(self.board_size_)] for j in range(self.board_size_)]
        board = terms[1].split(';')
        for i in range(len(board)):
            self.board_[i // self.board_size_][i % self.board_size_] = int(board[i])
            if int(board[i]) == 0:
                self.empty_pos_[0] = i // self.board_size_
                self.empty_pos_[1] = i % self.board_size_
    
    def slide(self, action_id, act=False):
        pos_r = self.empty_pos_[0]
        pos_c = self.empty_pos_[1]
        next_pos_r = pos_r
        next_pos_c = pos_c
        new_key = ''

        if action_id == SlidingPuzzleAction.UP.value:
            next_pos_r -= 1
        elif action_id == SlidingPuzzleAction.RIGHT.value:
            next_pos_c += 1
        elif action_id == SlidingPuzzleAction.DOWN.value:
            next_pos_r += 1
        elif action_id == SlidingPuzzleAction.LEFT.value:
            next_pos_c -= 1

        if not self.position_check(next_pos_r) or not self.position_check(next_pos_c):
            print('Error: Invalid action operation!')
            exit()

        self.swap(self.empty_pos_, [next_pos_r, next_pos_c])
        new_key = self.encode()
        if (not act):
            self.swap(self.empty_pos_, [next_pos_r, next_pos_c])
        return new_key
    
    def swap(self, pos1, pos2):
        tmp = self.board_[pos1[0]][pos1[1]]
        self.board_[pos1[0]][pos1[1]] = self.board_[pos2[0]][pos2[1]]
        self.board_[pos2[0]][pos2[1]] = tmp
    
    def position_check(self, pos_idx):
        return 0 <= pos_idx < self.board_size_


class SlidingPuzzleEnv:
    def __init__(self, size):
        self.board_size_ = size
        self.target_key = f'{self.board_size_}_'
        for i in range(1, size * size):
            self.target_key += f'{i};'
        self.target_key += '0'
        self.state_ = SlidingPuzzleState(self.target_key)

    def state_transition(self, state_key, action_id):
        self.state_.decode(state_key)
        if action_id >= len(SlidingPuzzleAction) or action_id < 0:
            print('Error: Invalid action id!')
            exit()
        return self.state_.slide(action_id)
    
    def valid_actions(self, state_key):
        self.state_.decode(state_key)
        action_list = []
        if self.state_.empty_pos_[0] > 0:
            action_list.append(SlidingPuzzleAction.UP.value)
        if self.state_.empty_pos_[1] < self.board_size_ - 1:
            action_list.append(SlidingPuzzleAction.RIGHT.value)
        if self.state_.empty_pos_[0] < self.board_size_ - 1:
            action_list.append(SlidingPuzzleAction.DOWN.value)
        if self.state_.empty_pos_[1] > 0:
            action_list.append(SlidingPuzzleAction.LEFT.value)
        return tuple(action_list)
    
    def astar_heuristic(self, state_key):
        self.state_.decode(state_key)
        manhattan = .0
        for r in range(self.board_size_):
            for c in range(self.board_size_):
                puzzle = self.state_.board_[r][c]
                if (puzzle == 0):
                    continue
                correct_r = (puzzle - 1) // self.board_size_
                correct_c = (puzzle - 1) % self.board_size_
                manhattan += abs(r - correct_r) + abs(c - correct_c)
        return manhattan

    def to_string(self):
        board_str = ''
        for r in range(self.board_size_):
            board_str += '+'
            for c in range(self.board_size_):
                board_str += '-+'
            board_str += '\n|'
            for c in range(self.board_size_):
                board_str += f'{self.state_.board_[r][c]}|'
            board_str += '\n'
        board_str += '+'
        for c in range(self.board_size_):
            board_str += '-+'
        board_str += '\n'
        return board_str
    
    def to_string_with_path(self, path):
        board_str = ''
        for key in path:
            self.state_.decode(key)
            board_str += self.to_string()
            board_str += '\n'
        return board_str
    
    def shuffle(self):
        previous_key = ''
        current_key = self.target_key
        num_moves = self.board_size_ * 3
        for i in range(num_moves):
            print(self.to_string())
            actions = self.valid_actions(current_key)
            next_key = previous_key
            while next_key == previous_key:
                choosed_idx = random.randint(0, len(actions) - 1)
                choosed_action = actions[choosed_idx]
                next_key = self.state_.slide(choosed_action)
            previous_key = current_key
            current_key = self.state_.slide(choosed_action, act=True)
        print(self.to_string())

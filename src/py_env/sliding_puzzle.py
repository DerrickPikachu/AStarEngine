from enum import Enum

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
    
    def slide(self, action_id):
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
        self.swap(self.empty_pos_, [next_pos_r, next_pos_c])
        return new_key
    
    def swap(self, pos1, pos2):
        tmp = self.board_[pos1[0]][pos1[1]]
        self.board_[pos1[0]][pos1[1]] = self.board_[pos2[0]][pos2[1]]
        self.board_[pos2[0]][pos2[1]] = tmp
    
    def position_check(self, pos_idx):
        return 0 <= pos_idx < self.board_size_


class SlidingPuzzleEnv:
    def __init__(self):
        self.state_ = SlidingPuzzleState('')

    def state_transition(self, state_key, action_id):
        self.state_.decode(state_key)
        # print(f'action id: {action_id}')
        if action_id >= len(SlidingPuzzleAction) or action_id < 0:
            print('Error: Invalid action id!')
            exit()
        return self.state_.slide(action_id)

import sys
import py_env.astar_engine
import py_env.sliding_puzzle

def run_sliding_puzzle():
    size = int(input('What is the board size: '))
    env = py_env.sliding_puzzle.SlidingPuzzleEnv(size)
    env.shuffle()
    astar = py_env.astar_engine.AStarEngine()
    astar.set_environment(env, py_env.sliding_puzzle.SlidingPuzzleState)
    path = astar.run()
    print(env.to_string_with_path(path))
    

def main():
    if len(sys.argv) != 2:
        print('Error: Invalid input parameter')
        print('Usage: python3 main.py [sliding_puzzle|your_py_env]')
        exit()
    run_target = sys.argv[1]

    if run_target == 'sliding_puzzle':
        run_sliding_puzzle()

if __name__ == "__main__":
    main()
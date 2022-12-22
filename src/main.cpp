#include <iostream>
#include <string>
#include <memory>
#include "a_star.h"
#include "maze.h"
#include "environment.h"

void run_maze() {
    std::shared_ptr<Environment> env = Maze::make_maze(10, 15);
    env->set_start_key("0_0");
    env->set_target_key("0_14");
    std::cerr << env->to_string() << std::endl;
    AStarEngine engine;
    engine.set_environment(env);
    Path founded_path = engine.run();
    std::cerr << env->to_string(founded_path) << std::endl;
}

int main(int argc, char** argv) {
    std::string run_target = "default";

    if (argc > 1) { run_target = std::string(argv[1]); }
    if (argc > 2) {
        std::cerr << "Error: Invalid input parameter" << std::endl;
        std::cerr << "Usage: ./main [default|maze|your cpp env]" << std::endl;
        exit(0);
    }

    if (run_target == "default") {
        run_maze();
    } else if (run_target == "maze") {
        run_maze();
    }
}
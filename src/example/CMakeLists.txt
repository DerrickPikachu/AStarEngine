add_library(maze grid.cpp maze.cpp)

target_include_directories(maze PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/../base"
)
target_link_libraries( maze PUBLIC
    base
)
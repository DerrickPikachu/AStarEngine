add_library(astar a_star.cpp)
target_include_directories(astar PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/../example"
    "${CMAKE_CURRENT_SOURCE_DIR}/../base"
)
target_link_libraries(astar PUBLIC
    base
    example
)
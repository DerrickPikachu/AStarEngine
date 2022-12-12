add_library(example grid.cpp maze.cpp)

target_include_directories(example PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/../base"
)
target_link_libraries(example PUBLIC
    base
)
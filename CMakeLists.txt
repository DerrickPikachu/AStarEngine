cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(AStarEngine)

add_subdirectory(src)
add_subdirectory(third_party)

find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS} ${gtest_SOURCE_DIR}/include)

add_executable(test src/test.cpp)

target_link_libraries(test PUBLIC
    gtest_main
    pybind11_headers
    ${PYTHON_LIBRARIES}
    base
    maze
    astar
)
target_include_directories(test PUBLIC
    "${PROJECT_SOURCE_DIR}/third_party/googletest"
    "${PROJECT_SOURCE_DIR}/third_party/pybind11"
)

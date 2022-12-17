cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -g -O3")

project(AStarEngine)

add_subdirectory(third_party)
add_subdirectory(src)

find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS} ${gtest_SOURCE_DIR}/include)

add_executable(test src/test.cpp)

target_link_libraries(test PUBLIC
    gtest_main
    pybind11_headers
    ${PYTHON_LIBRARIES}
    base
    example
    astar
)
target_include_directories(test PUBLIC
    "${PROJECT_SOURCE_DIR}/third_party/googletest"
    "${PROJECT_SOURCE_DIR}/third_party/pybind11"
)

pybind11_add_module(astar_engine src/python_wrapper.cpp)

target_link_libraries(astar_engine PUBLIC
    pybind11_headers
    ${PYTHON_LIBRARIES}
    base
    example
    astar
)
target_include_directories(astar_engine PUBLIC
    "${PROJECT_SOURCE_DIR}/third_party/pybind11"
)
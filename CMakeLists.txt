cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(AStarEngine)

add_subdirectory(src)
add_subdirectory(third_party)

add_executable(test src/test.cpp)

target_link_libraries(test PUBLIC gtest_main)
target_include_directories(test PUBLIC
                           "${PROJECT_SOURCE_DIR}/third_party/googletest")
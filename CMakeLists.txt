cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(AStarEngine)

add_subdirectory(src)
add_subdirectory(third_party)

# for GTest
include_directories(${gtest_SOURCE_DIR}/include)

add_executable(test src/test.cpp)

target_link_libraries(test PUBLIC src gtest_main)
target_include_directories(test PUBLIC
                           "${PROJECT_SOURCE_DIR}/src"
                           "${PROJECT_SOURCE_DIR}/third_party/googletest")
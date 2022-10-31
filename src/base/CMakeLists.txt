add_library(base environment.cpp state.cpp)
target_include_directories(base PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(base)
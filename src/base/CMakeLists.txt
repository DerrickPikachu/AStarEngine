add_library(base environment.cpp state.cpp python_try.cpp)

find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

target_include_directories(base PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/third_party/pybind11
)

target_link_libraries(base PUBLIC
    pybind11_headers
    "${PYTHON_LIBRARIES}"
)
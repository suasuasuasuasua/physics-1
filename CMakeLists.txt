cmake_minimum_required(VERSION 3.15)
project(
  # manually update these. using variable is sort of finnicky
  physics_1
  VERSION 0.1.0
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

set(PYBIND11_FINDPYTHON ON)
add_subdirectory(extern/pybind11)

python_add_library(_core MODULE src/main.cpp src/functions.cpp WITH_SOABI)

# This is passing in the version as a define just as an example
target_compile_definitions(_core PRIVATE VERSION_INFO=${PROJECT_VERSION})
target_include_directories(_core PRIVATE "${CMAKE_SOURCE_DIR}/inc/")

target_link_libraries(_core PRIVATE pybind11::headers)

# The install directory is the output (wheel) directory
install(TARGETS _core DESTINATION physics_1)

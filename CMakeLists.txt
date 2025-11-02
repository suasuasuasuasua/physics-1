cmake_minimum_required(VERSION 3.15)
set(PROJECT_VERSION 0.1.0)
project(
  # manually update these. using variable is sort of finnicky
  physics_1
  VERSION ${PROJECT_VERSION}
  LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(PYBIND11_FINDPYTHON ON)
add_subdirectory(extern/pybind11)

python_add_library(_core MODULE src/main.cpp src/example/functions.cpp
                   src/linalg/vector.cpp WITH_SOABI)

# This is passing in the version as a define just as an example
target_compile_definitions(_core PRIVATE VERSION_INFO=${PROJECT_VERSION})
target_include_directories(_core PRIVATE ${CMAKE_SOURCE_DIR}/inc)
target_link_libraries(_core PRIVATE pybind11::headers)

# The install directory is the output (wheel) directory
install(TARGETS _core DESTINATION physics_1)

# add the modules
add_subdirectory(src/example)
add_subdirectory(src/linalg)

# enable testing
enable_testing()
add_subdirectory(tests)

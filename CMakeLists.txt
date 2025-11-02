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

# add the modules
add_subdirectory(python)
add_subdirectory(src)
add_subdirectory(tests)

cmake_minimum_required(VERSION 3.15)
project(
  ${SKBUILD_PROJECT_NAME}
  VERSION ${SKBUILD_PROJECT_VERSION}
  LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "-Wextra -Wall")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Always build Python extension modules (only needs Development.Module)
add_subdirectory(python)

# Check if Development.Embed is available for embedding Python in C++
# This is needed for src/ and tests/ but not for wheel builds
find_package(Python COMPONENTS Development.Embed QUIET)
if(Python_Development.Embed_FOUND)
  message(STATUS "Python Development.Embed found - building src and tests")
  add_subdirectory(src)
  add_subdirectory(tests)
else()
  message(STATUS "Python Development.Embed not found - skipping src and tests (wheel build mode)")
endif()

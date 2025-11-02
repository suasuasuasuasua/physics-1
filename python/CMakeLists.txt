# Find Python before including pybind11 to ensure Python_SOABI is available
# for use with python_add_library(...WITH_SOABI)
find_package(Python 3.8 REQUIRED COMPONENTS Interpreter Development.Module
             OPTIONAL_COMPONENTS Development.Embed)

add_subdirectory(${CMAKE_SOURCE_DIR}/extern/pybind11
                 ${PROJECT_BINARY_DIR}/extern/pybind11)

python_add_library(
  _core MODULE main.cpp ${CMAKE_SOURCE_DIR}/src/example/functions.cpp
  ${CMAKE_SOURCE_DIR}/src/linalg/vector.cpp WITH_SOABI)

# This is passing in the version as a define just as an example
target_compile_definitions(_core PRIVATE VERSION_INFO=${PROJECT_VERSION})
target_include_directories(_core PRIVATE ${CMAKE_SOURCE_DIR}/inc)
target_link_libraries(_core PRIVATE pybind11::headers)

# The install directory is the output (wheel) directory
install(TARGETS _core DESTINATION physics_1)

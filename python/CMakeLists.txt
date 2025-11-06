find_package(Python COMPONENTS Interpreter Development.Module)

add_subdirectory(${CMAKE_SOURCE_DIR}/extern/pybind11
                 ${PROJECT_BINARY_DIR}/extern/pybind11)

pybind11_add_module(_core MODULE main.cpp WITH_SOABI)

# This is passing in the version as a define just as an example
target_compile_definitions(_core PRIVATE VERSION_INFO=${PROJECT_VERSION})

# The install directory is the output (wheel) directory
install(TARGETS _core DESTINATION physics_1)

add_subdirectory(physics_1/math)
add_subdirectory(physics_1/example)

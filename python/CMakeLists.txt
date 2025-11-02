set(PYBIND11_FINDPYTHON ON)

message(STATUS "Before add_subdirectory - Python_SOABI: ${Python_SOABI}")

add_subdirectory(${CMAKE_SOURCE_DIR}/extern/pybind11
                 ${PROJECT_BINARY_DIR}/extern/pybind11)

message(STATUS "After add_subdirectory - Python_SOABI: ${Python_SOABI}")

# Try to get it from cache or set it manually
if(NOT DEFINED Python_SOABI OR Python_SOABI STREQUAL "")
  message(STATUS "Python_SOABI not set, trying to compute it...")
  execute_process(
    COMMAND "${Python_EXECUTABLE}" "-c" "import sysconfig; print(sysconfig.get_config_var('SOABI'))"
    OUTPUT_VARIABLE Python_SOABI
    OUTPUT_STRIP_TRAILING_WHITESPACE)
  message(STATUS "Computed Python_SOABI: ${Python_SOABI}")
endif()

python_add_library(
  _core MODULE main.cpp ${CMAKE_SOURCE_DIR}/src/example/functions.cpp
  ${CMAKE_SOURCE_DIR}/src/linalg/vector.cpp WITH_SOABI)

get_target_property(SUFFIX _core SUFFIX)
message(STATUS "Final SUFFIX: ${SUFFIX}")

# This is passing in the version as a define just as an example
target_compile_definitions(_core PRIVATE VERSION_INFO=${PROJECT_VERSION})
target_include_directories(_core PRIVATE ${CMAKE_SOURCE_DIR}/inc)
target_link_libraries(_core PRIVATE pybind11::headers)

# The install directory is the output (wheel) directory
install(TARGETS _core DESTINATION physics_1)

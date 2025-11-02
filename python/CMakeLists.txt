set(PYBIND11_FINDPYTHON ON)

add_subdirectory(${CMAKE_SOURCE_DIR}/extern/pybind11
                 ${PROJECT_BINARY_DIR}/extern/pybind11)

# pybind11 finds Python in its own scope, but Python_SOABI doesn't propagate
# to the parent scope. We need to set it manually for python_add_library WITH_SOABI
# to work correctly.
if(NOT DEFINED Python_SOABI OR Python_SOABI STREQUAL "")
  if(NOT DEFINED Python_EXECUTABLE)
    message(
      FATAL_ERROR
        "Python_EXECUTABLE is not defined. Ensure Python is found before this point.")
  endif()
  
  execute_process(
    COMMAND "${Python_EXECUTABLE}" "-c"
            "import sysconfig; print(sysconfig.get_config_var('SOABI'))"
    OUTPUT_VARIABLE Python_SOABI
    RESULT_VARIABLE _PYTHON_SOABI_RESULT
    ERROR_VARIABLE _PYTHON_SOABI_ERROR
    OUTPUT_STRIP_TRAILING_WHITESPACE)
  
  if(NOT _PYTHON_SOABI_RESULT EQUAL 0)
    message(
      FATAL_ERROR
        "Failed to determine Python_SOABI. Python command failed with:\n${_PYTHON_SOABI_ERROR}")
  endif()
endif()

python_add_library(
  _core MODULE main.cpp ${CMAKE_SOURCE_DIR}/src/example/functions.cpp
  ${CMAKE_SOURCE_DIR}/src/linalg/vector.cpp WITH_SOABI)

# This is passing in the version as a define just as an example
target_compile_definitions(_core PRIVATE VERSION_INFO=${PROJECT_VERSION})
target_include_directories(_core PRIVATE ${CMAKE_SOURCE_DIR}/inc)
target_link_libraries(_core PRIVATE pybind11::headers)

# The install directory is the output (wheel) directory
install(TARGETS _core DESTINATION physics_1)

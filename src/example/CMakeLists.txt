add_library(example SHARED)
target_sources(
  example
  PRIVATE functions.cpp
  PUBLIC FILE_SET HEADERS BASE_DIRS ${CMAKE_SOURCE_DIR}/inc FILES
         ${CMAKE_SOURCE_DIR}/inc/example/functions.h)

target_compile_definitions(example PRIVATE VERSION_INFO=${PROJECT_VERSION})
target_link_libraries(example PRIVATE pybind11::embed)

# Install shared library alongside Python module
install(TARGETS example DESTINATION physics_1)

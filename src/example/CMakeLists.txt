add_library(example)
target_sources(
  example
  PRIVATE functions.cpp example.cpp
  PUBLIC FILE_SET HEADERS BASE_DIRS ${CMAKE_SOURCE_DIR}/inc FILES
         ${CMAKE_SOURCE_DIR}/inc/example/functions.h
         ${CMAKE_SOURCE_DIR}/inc/example/example_bindings.h)

target_compile_definitions(example PRIVATE VERSION_INFO=${PROJECT_VERSION})
set_target_properties(example PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_link_libraries(example PRIVATE pybind11::embed)

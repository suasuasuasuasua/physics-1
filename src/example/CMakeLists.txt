add_library(example)
target_sources(
  example
  PRIVATE functions.cpp
  PUBLIC FILE_SET HEADERS BASE_DIRS ${CMAKE_SOURCE_DIR}/inc FILES
         ${CMAKE_SOURCE_DIR}/inc/example/functions.h)

target_compile_definitions(example PRIVATE VERSION_INFO=${PROJECT_VERSION})
set_target_properties(example PROPERTIES POSITION_INDEPENDENT_CODE ON)

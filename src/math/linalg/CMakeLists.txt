add_library(linalg)
target_sources(
  linalg
  PRIVATE vector.cpp
  PUBLIC FILE_SET HEADERS BASE_DIRS ${CMAKE_SOURCE_DIR}/inc FILES
         ${CMAKE_SOURCE_DIR}/inc/math/linalg/vector.h)

target_compile_definitions(linalg PRIVATE VERSION_INFO=${PROJECT_VERSION})
set_target_properties(linalg PROPERTIES POSITION_INDEPENDENT_CODE ON)

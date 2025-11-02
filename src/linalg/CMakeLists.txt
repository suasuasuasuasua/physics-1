add_library(linalg)
target_sources(
  linalg
  PRIVATE vector.cpp
  PUBLIC FILE_SET HEADERS BASE_DIRS ${CMAKE_SOURCE_DIR}/inc/math/linalg FILES
         ${CMAKE_SOURCE_DIR}/inc/math/linalg/vector.h)

target_compile_definitions(linalg PRIVATE VERSION_INFO=${PROJECT_VERSION})
target_include_directories(linalg PRIVATE ${CMAKE_SOURCE_DIR}/inc)
target_link_libraries(linalg PRIVATE pybind11::embed)

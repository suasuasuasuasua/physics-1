add_library(linalg SHARED)
target_sources(
  linalg
  PRIVATE vector.cpp
  PUBLIC FILE_SET HEADERS BASE_DIRS ${CMAKE_SOURCE_DIR}/inc FILES
         ${CMAKE_SOURCE_DIR}/inc/math/linalg/vector.h)

target_compile_definitions(linalg PRIVATE VERSION_INFO=${PROJECT_VERSION})
target_link_libraries(linalg PRIVATE pybind11::embed)

# Install shared library alongside Python module
install(TARGETS linalg DESTINATION physics_1)

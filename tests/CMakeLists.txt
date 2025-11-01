add_subdirectory(${CMAKE_SOURCE_DIR}/extern/googletest
                 ${PROJECT_BINARY_DIR}/extern/googletest)

add_executable(hello_test cpp/test_example.cpp
                          ${CMAKE_SOURCE_DIR}/src/example/functions.cpp)
target_include_directories(hello_test PRIVATE ${CMAKE_SOURCE_DIR}/inc/)
target_link_libraries(hello_test PRIVATE pybind11::embed GTest::gtest_main)

add_executable(linalg_test cpp/test_linalg.cpp
                           ${CMAKE_SOURCE_DIR}/src/linalg/vector.cpp)
target_include_directories(linalg_test PRIVATE ${CMAKE_SOURCE_DIR}/inc/)
target_link_libraries(linalg_test PRIVATE pybind11::embed GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(hello_test)
gtest_discover_tests(linalg_test)

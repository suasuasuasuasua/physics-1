add_subdirectory(${CMAKE_SOURCE_DIR}/extern/googletest
                 ${PROJECT_BINARY_DIR}/extern/googletest)

enable_testing()

add_executable(example_test cpp/test_example.cpp)
target_include_directories(example_test PRIVATE ${CMAKE_SOURCE_DIR}/inc/)
target_link_libraries(example_test PRIVATE pybind11::embed GTest::gtest_main
                                           example)

add_executable(linalg_test cpp/test_linalg.cpp)
target_include_directories(linalg_test PRIVATE ${CMAKE_SOURCE_DIR}/inc/)
target_link_libraries(linalg_test PRIVATE pybind11::embed GTest::gtest_main
                                          linalg)

include(GoogleTest)
gtest_discover_tests(example_test)
gtest_discover_tests(linalg_test)

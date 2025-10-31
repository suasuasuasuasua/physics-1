# Adding C++ Unit Tests with Google Test

This guide explains how to add C++ unit testing to your physics project using Google Test.

## Why C++ Tests?

While Python tests are great for integration testing and problem solving, C++ tests offer:
- **Fast execution**: No Python overhead
- **Development feedback**: Test C++ logic before exposing to Python
- **Type safety**: Catch type-related issues at compile time
- **Learning**: Deeper understanding of test frameworks

## Setup Instructions

### 1. Add Google Test as a Submodule

```bash
cd extern
git submodule add https://github.com/google/googletest.git
git submodule update --init --recursive
```

### 2. Update CMakeLists.txt

Add this after the existing pybind11 section:

```cmake
# Google Test setup
option(BUILD_TESTS "Build C++ tests" ON)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(extern/googletest)
    
    # Create test executable
    add_executable(physics_tests
        tests/cpp/test_kinematics.cpp
        src/kinematics.cpp
    )
    
    target_link_libraries(physics_tests 
        PRIVATE 
        gtest 
        gtest_main
    )
    
    target_include_directories(physics_tests PRIVATE inc)
    
    # Register with CTest
    include(GoogleTest)
    gtest_discover_tests(physics_tests)
endif()
```

### 3. Update Makefile

Add convenience commands:

```makefile
# Build C++ tests
build-tests:
	cmake -B build -DBUILD_TESTS=ON
	cmake --build build

# Run C++ tests
test-cpp:
	cd build && ctest --output-on-failure

# Run all tests
test-all: test test-cpp
```

### 4. Write Tests

See `tests/cpp/test_kinematics.cpp` for examples. Basic pattern:

```cpp
#include <gtest/gtest.h>
#include "physics/kinematics/motion.h"

TEST(KinematicsTest, TestName) {
    double result = physics::kinematics::position(0, 10, 5, 0);
    EXPECT_DOUBLE_EQ(result, 50.0);
}
```

### 5. Build and Run

```bash
# Build everything including tests
make build-tests

# Run C++ tests
make test-cpp

# Or use ctest directly
cd build
ctest --verbose
```

## Best Practices

### 1. Test C++ First, Then Python
```
1. Write C++ function
2. Write C++ test
3. Add Python binding
4. Write Python test
```

### 2. Use Fixtures for Common Setup
```cpp
class FreeFallTest : public ::testing::Test {
protected:
    const double g = 9.8;
    const double epsilon = 1e-6;
};

TEST_F(FreeFallTest, DroppedFromHeight) {
    // Test code here
}
```

### 3. Test Edge Cases
```cpp
TEST(KinematicsTest, ZeroTimeThrows) {
    EXPECT_THROW(
        physics::kinematics::velocity(100.0, 0.0),
        std::invalid_argument
    );
}
```

## Example: Complete Test Suite

```cpp
#include <gtest/gtest.h>
#include "physics/kinematics/motion.h"

class KinematicsTest : public ::testing::Test {
protected:
    static constexpr double g = 9.8;
    static constexpr double eps = 1e-6;
};

TEST_F(KinematicsTest, ObjectAtRestStaysAtRest) {
    double x = physics::kinematics::position(10.0, 0.0, 5.0, 0.0);
    EXPECT_DOUBLE_EQ(x, 10.0);
}

TEST_F(KinematicsTest, ConstantVelocityMovesLinearly) {
    double x = physics::kinematics::position(0.0, 5.0, 10.0, 0.0);
    EXPECT_DOUBLE_EQ(x, 50.0);
}
```

See the full guide in the file for more details!

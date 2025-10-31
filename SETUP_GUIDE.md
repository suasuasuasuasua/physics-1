# Physics Learning Project - Setup and Usage Guide

## Overview

This repository implements a hybrid C++/Python approach for learning physics concepts through code. The setup allows you to:

1. **Implement physics concepts in C++** for performance and deep understanding
2. **Expose C++ functions to Python** via pybind11 for easy experimentation
3. **Write unit tests** for practice problems and exam questions
4. **Validate your understanding** through automated testing

## Architecture

### Directory Structure

```
physics-1/
├── inc/                  # C++ header files
│   └── physics/          # Physics concept headers
│       ├── kinematics/   # Position, velocity, acceleration
│       ├── dynamics/     # Forces, Newton's laws
│       ├── energy/       # Work, energy, power
│       └── momentum/     # Momentum, collisions
├── src/
│   ├── main.cpp          # pybind11 bindings
│   └── physics_1/        # Python package
│       ├── __init__.py   # Python module initialization
│       └── __init__.pyi  # Type stubs
├── tests/
│   ├── cpp/              # C++ unit tests (Google Test)
│   │   ├── test_kinematics.cpp
│   │   ├── test_dynamics.cpp
│   │   └── ...
│   └── python/           # Python integration tests
│       ├── test_kinematics.py
│       ├── test_dynamics.py
│       └── test_exam_problems.py
├── extern/               # Third-party dependencies
│   ├── pybind11/         # Python bindings
│   └── googletest/       # C++ testing framework
├── CMakeLists.txt        # Build configuration
├── pyproject.toml        # Python package configuration
└── Makefile              # Convenience commands
```

## Setup Instructions

### 1. Initialize Submodules

```bash
git submodule update --init --recursive
```

### 2. Install Python Dependencies

```bash
pip install -e .[dev]
```

This installs:
- `numpy` - For numerical operations
- `pytest` - For Python testing
- `ruff` - For Python linting
- `build` - For building Python wheels

### 3. Build the C++ Extension

The package uses scikit-build-core which automatically builds the C++ extension when you install with pip.

## Development Workflow

### Implementing a Physics Concept

#### Step 1: Create C++ Header (inc/physics/)

```cpp
// inc/physics/kinematics/velocity.h
#pragma once
#include <vector>

namespace physics {
namespace kinematics {

// Calculate velocity from displacement and time
double velocity(double displacement, double time);

// Calculate average velocity from positions and times
double average_velocity(const std::vector<double>& positions,
                       const std::vector<double>& times);

} // namespace kinematics
} // namespace physics
```

#### Step 2: Implement in C++ (src/)

```cpp
// src/kinematics.cpp
#include "physics/kinematics/velocity.h"
#include <stdexcept>

namespace physics {
namespace kinematics {

double velocity(double displacement, double time) {
    if (time <= 0) {
        throw std::invalid_argument("Time must be positive");
    }
    return displacement / time;
}

double average_velocity(const std::vector<double>& positions,
                       const std::vector<double>& times) {
    if (positions.size() != times.size() || positions.empty()) {
        throw std::invalid_argument("Invalid input");
    }
    double total_displacement = positions.back() - positions.front();
    double total_time = times.back() - times.front();
    return velocity(total_displacement, total_time);
}

} // namespace kinematics
} // namespace physics
```

#### Step 3: Add Python Bindings (src/main.cpp)

```cpp
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "physics/kinematics/velocity.h"

namespace py = pybind11;

PYBIND11_MODULE(_core, m) {
    // Create submodule for kinematics
    auto kinematics = m.def_submodule("kinematics", "Kinematics functions");
    
    kinematics.def("velocity", &physics::kinematics::velocity,
        py::arg("displacement"), py::arg("time"),
        R"pbdoc(
            Calculate velocity from displacement and time.
            
            Parameters
            ----------
            displacement : float
                Displacement in meters
            time : float
                Time in seconds
                
            Returns
            -------
            float
                Velocity in m/s
        )pbdoc");
}
```

#### Step 4: Write C++ Unit Tests (tests/cpp/)

```cpp
// tests/cpp/test_kinematics.cpp
#include <gtest/gtest.h>
#include "physics/kinematics/velocity.h"

TEST(VelocityTest, BasicCalculation) {
    double displacement = 100.0;  // meters
    double time = 10.0;           // seconds
    double expected = 10.0;       // m/s
    
    EXPECT_DOUBLE_EQ(physics::kinematics::velocity(displacement, time), expected);
}

TEST(VelocityTest, NegativeDisplacement) {
    EXPECT_DOUBLE_EQ(physics::kinematics::velocity(-50.0, 5.0), -10.0);
}

TEST(VelocityTest, ZeroTimeThrows) {
    EXPECT_THROW(physics::kinematics::velocity(100.0, 0.0), std::invalid_argument);
}
```

#### Step 5: Write Python Tests (tests/python/)

```python
# tests/python/test_kinematics.py
import pytest
import physics_1 as phys

def test_velocity_basic():
    """Test basic velocity calculation."""
    displacement = 100.0  # meters
    time = 10.0           # seconds
    expected = 10.0       # m/s
    
    assert phys.kinematics.velocity(displacement, time) == expected

def test_exam_problem_1():
    """
    Exam Problem: A car travels 150 km in 2 hours.
    What is its average velocity in m/s?
    """
    displacement = 150_000  # 150 km in meters
    time = 2 * 3600         # 2 hours in seconds
    
    velocity = phys.kinematics.velocity(displacement, time)
    
    # Expected: 150000 / 7200 = 20.83 m/s
    assert abs(velocity - 20.833333) < 0.001

def test_practice_problem_projectile():
    """
    Practice Problem: A projectile is launched upward at 30 m/s.
    How long until it returns to ground? (ignore air resistance)
    """
    initial_velocity = 30.0  # m/s
    g = 9.8                  # m/s^2
    
    # Time to peak: v = v0 - gt, when v=0
    time_to_peak = initial_velocity / g
    total_time = 2 * time_to_peak
    
    assert abs(total_time - 6.122) < 0.01
```

### Building and Testing

```bash
# Install/rebuild the package
make install

# Run Python tests
make test

# Run C++ tests (if configured)
cd build && ctest

# Format code
make format

# Lint code
make lint
```

## Tips for Learning Physics with This Setup

### 1. Start with Fundamentals
- Begin with kinematics (position, velocity, acceleration)
- Move to dynamics (forces, Newton's laws)
- Progress to energy and momentum

### 2. Implement Practice Problems as Tests
- Each practice problem becomes a test case
- Tests serve as documentation of your learning
- Automated validation ensures correctness

### 3. Use Python for Visualization
```python
import physics_1 as phys
import matplotlib.pyplot as plt
import numpy as np

# Simulate projectile motion
times = np.linspace(0, 10, 100)
positions = [phys.kinematics.position(v0=50, t=t, a=-9.8) for t in times]

plt.plot(times, positions)
plt.xlabel('Time (s)')
plt.ylabel('Height (m)')
plt.title('Projectile Motion')
plt.show()
```

### 4. Organize by Topic
Create separate modules for each physics topic:
- `physics::kinematics` - Motion without forces
- `physics::dynamics` - Forces and Newton's laws  
- `physics::energy` - Work, kinetic energy, potential energy
- `physics::momentum` - Linear and angular momentum
- `physics::oscillations` - Springs, pendulums, SHM
- `physics::waves` - Wave motion, interference

### 5. Document Your Learning
Use test docstrings to explain:
- The physics concept being tested
- The problem statement
- The solution approach
- References to course material

## Example: Complete Implementation

### Problem: Constant Acceleration Motion

```cpp
// inc/physics/kinematics/motion.h
#pragma once

namespace physics::kinematics {

// Position with constant acceleration
// x = x0 + v0*t + 0.5*a*t^2
double position(double x0, double v0, double t, double a);

// Velocity with constant acceleration
// v = v0 + a*t
double velocity_at_time(double v0, double t, double a);

// Velocity from kinematics equation
// v^2 = v0^2 + 2*a*(x - x0)
double velocity_from_position(double v0, double x, double x0, double a);

} // namespace physics::kinematics
```

```python
# tests/python/test_motion.py
import physics_1 as phys

def test_free_fall():
    """
    Problem: Drop a ball from 100m height.
    How long to hit ground? What's final velocity?
    """
    h0 = 100.0  # initial height (m)
    v0 = 0.0    # initial velocity (m/s)
    g = -9.8    # acceleration due to gravity (m/s^2)
    
    # Solve: 0 = h0 + v0*t + 0.5*g*t^2
    # Using quadratic formula
    import math
    t = math.sqrt(-2 * h0 / g)
    
    # Calculate final velocity
    v_final = phys.kinematics.velocity_at_time(v0, t, g)
    
    assert abs(t - 4.515) < 0.01
    assert abs(v_final - (-44.27)) < 0.1
```

## Advantages of This Hybrid Approach

### C++ Benefits
- **Performance**: Fast numerical computations
- **Type Safety**: Catch errors at compile time
- **Learning**: Deep understanding of implementation
- **Portability**: Core logic separate from Python

### Python Benefits
- **Rapid Prototyping**: Quick experimentation
- **Visualization**: Easy plotting with matplotlib
- **Data Analysis**: NumPy/SciPy integration
- **Interactive**: IPython/Jupyter notebooks

### Testing Benefits
- **Automated Validation**: Ensure correctness
- **Regression Prevention**: Catch bugs early
- **Documentation**: Tests explain usage
- **Learning Tool**: Practice problems as tests

## Resources

### Physics
- [MIT OpenCourseWare - Classical Mechanics](https://ocw.mit.edu/courses/8-01sc-classical-mechanics-fall-2016/)
- [The Feynman Lectures on Physics](https://www.feynmanlectures.caltech.edu/)

### C++ and Python Integration
- [pybind11 Documentation](https://pybind11.readthedocs.io/)
- [scikit-build-core](https://scikit-build-core.readthedocs.io/)

### Testing
- [Google Test Documentation](https://google.github.io/googletest/)
- [pytest Documentation](https://docs.pytest.org/)

## Next Steps

1. ✅ Fix Python version requirement (done: changed to >=3.12)
2. Add Google Test for C++ unit testing
3. Create example kinematics module
4. Implement first practice problem from MIT OCW
5. Add visualization examples with matplotlib
6. Document more physics concepts as you learn them

Happy learning! 🚀

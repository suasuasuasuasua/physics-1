# Physics 1

> A repository dedicated to me learning physics from the ground up.

I have always been interested in physics, but I've only ever taken two classes
in my time at college (physics 1 and 2). Though I did well, I don't feel like I
truly grasped the material; I only learned how to take tests and do homework.

This repository has a few goals

- Work through an undergraduate level physics class at my own pace to fully
understand the material
- Improve my C++ skills outside of work
- Work through and implement the practice problems as test cases to ensure that
my code works

## 🚀 Quick Start

```bash
# Clone and initialize
git clone https://github.com/suasuasuasuasua/physics-1.git
cd physics-1
git submodule update --init --recursive

# Install
pip install -e .[dev]

# Run tests
make test

# Try it out
python -c "import physics_1 as p; print(p.kinematics.velocity_at_time(0, 5, 9.8))"
```

## 📚 Documentation

See [SETUP_GUIDE.md](SETUP_GUIDE.md) for:
- Detailed setup instructions
- Development workflow
- How to implement physics concepts
- Example problems and solutions
- Tips for learning physics through code

## 🏗️ Architecture

**Hybrid C++/Python Approach:**
- Implement physics concepts in C++ for performance and deep understanding
- Expose to Python via pybind11 for easy experimentation and visualization
- Write unit tests as practice problems to validate correctness

**Structure:**
```
inc/physics/          # C++ headers organized by topic
  ├── kinematics/     # Motion equations
  ├── dynamics/       # Forces and Newton's laws
  └── energy/         # Work, energy, power
src/                  # C++ implementations + Python bindings
tests/                # Python and C++ unit tests
```

## ✅ Current Implementation

- ✅ Kinematics module (position, velocity, acceleration)
- ✅ Python bindings via pybind11
- ✅ Test suite with physics problems
- ⏳ Dynamics (forces, Newton's laws) - Coming soon
- ⏳ Energy and momentum - Coming soon

## 🧪 Example Usage

```python
import physics_1 as phys

# Free fall problem: ball dropped from 100m
g = -9.8  # m/s^2
h0 = 100.0  # m
v0 = 0.0  # m/s (dropped, not thrown)

# How long to hit ground?
time = phys.kinematics.time_to_position(h0, 0, v0, g)
print(f"Time to ground: {time:.2f} seconds")

# What's the final velocity?
v_final = phys.kinematics.velocity_at_time(v0, time, g)
print(f"Impact velocity: {v_final:.2f} m/s")
```

## Course Material

- [MIT Course Wave](https://ocw.mit.edu/courses/8-01sc-classical-mechanics-fall-2016/)

## References

- The CMake example from [scikit](https://github.dev/pybind/scikit_build_example)
- [pybind11 Documentation](https://pybind11.readthedocs.io/)

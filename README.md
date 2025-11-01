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

## Quick Start

Ensure that these programs are installed.

```text
cmake
gcc (or any C/C++ copmiler like clang)
make
python3.13
```

See `devenv.nix` for automatic installation using `nix`.

### Initial Setup

```bash
# Clone the repository
git clone https://github.com/suasuasuasuasua/physics-1.git
cd physics-1

# Initialize submodules (required for pybind11 and googletest)
git submodule update --init --recursive

# Install the package
make install
# or: pip install .
```

### Common Commands

The `Makefile` has the following utility functions.

```bash
# build the C++ code (for development)
make build

# install the python package
make install

# build the python wheel file
make wheel

# run tests in the tests/ folder
make test

# generate type stubs for IDE support
make stubs

# clean the cached directory
make clean
```

### Understanding the Build System

New to the project or confused about how the Python/C++ build system works? 

👉 **Check out the [docs/](docs/) directory for comprehensive documentation:**

- **[Build Architecture](docs/build-architecture.md)** - Detailed explanation of how pyproject.toml, CMakeLists.txt, and pybind11 work together
- **[Build Flow Diagrams](docs/build-flow-diagrams.md)** - Visual representations of the build process
- **[FAQ and Troubleshooting](docs/faq-and-troubleshooting.md)** - Common questions and solutions

The documentation explains:
- How `pip install .` understands to build from CMakeLists.txt
- Why the `src/physics_1/` folder must be structured the way it is
- How the C++ code connects to Python through pybind11
- Why stub files (`.pyi`) are needed and how to generate them
- Troubleshooting common build and import errors

## Course Material

- [MIT Course Wave](https://ocw.mit.edu/courses/8-01sc-classical-mechanics-fall-2016/)

## References

- [pybind11 Documentation](https://pybind11.readthedocs.io/en/stable/)
- The CMake example from [scikit](https://github.com/pybind/scikit_build_example)
